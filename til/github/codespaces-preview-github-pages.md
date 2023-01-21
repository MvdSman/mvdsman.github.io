# Codespaces: Preview GitHub Pages

GitHub Codespaces allows for using an IDE like VSCode in the web browser in a Virtual Machine (VM), hosted by and integrated with GitHub.

To locally preview GitHub Pages, you'd need Jekyll and Ruby. However, using Codespaces, you can simply start up the VM with a preset of Jekyll and Ruby installs to preview your pages wherever and whenever.

The following steps allow you to preview GitHub Pages in Codespaces:

1. With a already-created GitHub repository open in your web browser, click on Code -> Codespaces and launch a (new) instance
2. In the Codespaces instance, open the terminal and clone the [vscode devcontainers repo](https://github.com/microsoft/vscode-dev-containers): `git clone https://github.com/devcontainers/images.git`
3. Using the file browser on the left (assuming VS Code is used):
   1. Select the `/images/src/jekyll/.devcontainer/` folder and copy-paste it into the root of your own Repository (root of the file browser)
   2. Delete the folder `/vscode-dev-containers/` since this its contents are no longer needed
4. Push the newly created `/.devcontainer/` changes to the origin to make sure Codespaces can build with the new container
5. Restart your Codespaces instance (on start-up it will install the required packages)
6. To run:
   - If your Jekyll project contains a `Gemfile` in the root folder, the development container will install all gems at startup by running `bundle install`. This is the [recommended](https://jekyllrb.com/docs/step-by-step/10-deployment/#gemfile) approach as it allows you to specify the exact Jekyll version your project requires and list all additional Jekyll plugins.
   - If there's no `Gemfile`, the development container will install Jekyll automatically, picking the latest version. You might need to manually install the other dependencies your project relies on, including all relevant Jekyll plugins.

      > Refer to [this guide](https://containers.dev/guide/dockerfile) for more details.

# References

- [GitHub Codespaces with GitHub Pages](https://www.youtube.com/watch?v=8KwoKgYz85k)
- [GitHub Devcontainers - Images](https://github.com/devcontainers/images/tree/main/src/jekyll)