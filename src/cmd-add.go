package main

import (
	"fmt"

	"github.com/pterm/pterm"
	"github.com/spf13/cobra"
)

var AddCmd = &cobra.Command{
	Use:   "add",
	Short: "add a dependency",
	Run: func(cmd *cobra.Command, args []string) {
		var result AddDependencyResult
		for _, dep := range args {
			version := "^0"
			if len(args) > 1 {
				version = args[1]
			}
			_ = version
			result = MainSea.AddDependency(dep, version)
		}
		MainSea.Save()

		// print results
		header := pterm.NewStyle(pterm.FgGreen, pterm.BgDefault)
		dep_list := pterm.LeveledList{}
		dep_list = append(dep_list, pterm.LeveledListItem{Level: 0, Text: header.Sprint("Direct dependencies")})
		for name, version := range result.Direct {
			dep_list = append(dep_list, pterm.LeveledListItem{Level: 1, Text: fmt.Sprintf("%s@%s", name, version)})
		}
		dep_list = append(dep_list, pterm.LeveledListItem{Level: 0, Text: header.Sprint("All dependencies")})
		for name, version := range result.All {
			dep_list = append(dep_list, pterm.LeveledListItem{Level: 1, Text: fmt.Sprintf("%s@%s", name, version)})
		}
		root := pterm.NewTreeFromLeveledList(dep_list)
		pterm.DefaultTree.WithRoot(root).Render()
	},
}
