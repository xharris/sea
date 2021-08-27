package main

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"
)

type StringMap = map[string]string

var RootCmd = &cobra.Command{
	Use: "cpack",
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("hi")
	},
}
var MainSea Sea

func main() {
	RootDir, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
	}
	MainSea = Sea{
		Path: RootDir,
	}
	MainSea.Load()

	RootCmd.AddCommand(AddCmd)

	if err := RootCmd.Execute(); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
