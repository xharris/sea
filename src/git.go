package main

import (
	"bytes"
	"fmt"
	"os/exec"
	"strings"

	"github.com/Masterminds/semver"
)

func Clone(url string, version *string) {
	*version = getLatestVersion(url)
	fmt.Println(url, *version)
}

func ValidateVersion(want string, version string) bool {
	want_ver, err := semver.NewConstraint(want)
	if err != nil {
		fmt.Println(err)
	}
	ver, err := semver.NewVersion(version)
	if err != nil {
		fmt.Println(version)
	}
	return want_ver.Check(ver)
}

// returns map[hash string]version string
func GetVersionList(url string) StringMap {
	// get git version list string
	cmd := exec.Command("git", "ls-remote", "--tags", url)
	var (
		stderr bytes.Buffer
		out    bytes.Buffer
	)
	cmd.Stdout = &out
	cmd.Stderr = &stderr
	err := cmd.Run()
	if err != nil {
		fmt.Println(fmt.Sprint(err) + ":" + stderr.String())
	}
	// break it down
	ret := make(StringMap)
	versions := strings.Split(out.String(), "\n")
	for _, line := range versions {
		hash_ver := strings.Split(line, "\t")
		if len(hash_ver) == 2 {
			ret[hash_ver[0]] = strings.ReplaceAll(hash_ver[1], "refs/tags/", "")
		}
	}
	return ret
}

func getLatestVersion(url string) string {
	versions := GetVersionList(url)
	var latest string
	var latest_ver *semver.Constraints
	var current_ver *semver.Version
	var err error
	for _, ver := range versions {
		current_ver, err = semver.NewVersion(ver)
		if err != nil {
			fmt.Println(err)
		}
		if latest == "" || latest_ver.Check(current_ver) {
			// found a version that's later
			latest = ver
			latest_ver, err = semver.NewConstraint(">=" + latest)
			if err != nil {
				fmt.Println(err)
			}
		}
	}
	return "^" + latest
}
