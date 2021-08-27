package main

import (
	"fmt"
	"regexp"

	"github.com/spf13/viper"
)

type Sea struct {
	Path   string
	Config viper.Viper
}

func (sea *Sea) Load() {
	sea.Config = *viper.New()
	sea.Config.SetConfigName("sea")
	sea.Config.SetConfigType("json")
	sea.Config.AddConfigPath(sea.Path)
	// parse config
	err := sea.Config.ReadInConfig()
	if err != nil {
		fmt.Println(err)
	}
}

type AddDependencyResult struct {
	Direct StringMap
	All    StringMap
}

var re_git = regexp.MustCompile(`(?:git)?(?:\+https?:\/\/.+@|:\/\/)?(?P<Url>.+git)(?P<Version>#.*)?`)

func (sea *Sea) AddDependency(name string, version string) AddDependencyResult {
	result := AddDependencyResult{Direct: make(StringMap), All: make(StringMap)}

	var deps map[string]string
	sea.Config.UnmarshalKey("dependencies", &deps)
	// add...
	res_git := re_git.FindStringSubmatch(name)
	if len(res_git) > 0 {
		// GetVersionCommit("https://"+res_git[1], version)
		name = res_git[1]
		Clone("https://"+res_git[1], &version)
	}

	result.Direct[name] = version
	result.All[name] = version

	deps[name] = version
	sea.Config.Set("dependencies", deps)
	return result
}

func (sea *Sea) Save() {
	sea.Config.WriteConfig()
}
