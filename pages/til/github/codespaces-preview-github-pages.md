# Codespaces: Preview GitHub Pages

GitHub Codespaces allows for using an IDE like VSCode in the web browser in a Virtual Machine (VM), hosted by and integrated with GitHub.

To locally preview GitHub Pages, you'd need Jekyll and Ruby. However, using Codespaces, you can simply start up the VM with a preset of Jekyll and Ruby installs to preview your pages wherever and whenever.

## How to

The following steps allow you to preview GitHub Pages in Codespaces:

1. With a already-created GitHub repository open in your web browser, click on Code -> Codespaces and launch a (new) instance
2. In the Codespaces instance, open the terminal and clone the [vscode devcontainers repo](https://github.com/microsoft/vscode-dev-containers): `git clone https://github.com/devcontainers/images.git`
3. Using the file browser on the left (assuming VS Code is used):
   1. Select the `/images/src/jekyll/.devcontainer/` folder and copy-paste it into the root of your own Repository (root of the file browser)
   2. Delete the folder `/vscode-dev-containers/` since this its contents are no longer needed
4. In `/.devcontainer/devcontainer.json`, set the value of `"remoteUser"` to `"root"`
5. Push the newly created `/.devcontainer/` changes to the origin to make sure Codespaces can build with the new container
6. Rebuild or restart your Codespaces instance (on start-up it will install the required packages)
7. To run:
   - If your Jekyll project contains a `Gemfile` in the root folder, the development container will install all gems at startup by running `bundle install`. This is the [recommended](https://jekyllrb.com/docs/step-by-step/10-deployment/#gemfile) approach as it allows you to specify the exact Jekyll version your project requires and list all additional Jekyll plugins.
   - If there's no `Gemfile`, the development container will install Jekyll automatically, picking the latest version. You might need to manually install the other dependencies your project relies on, including all relevant Jekyll plugins.

      > Refer to [this guide](https://containers.dev/guide/dockerfile) for more details.
8. Serve the Jekyll site locally: `bundle exec jekyll serve`.
   
   This command expects a Gemfile to be present. If it's not present:

   1. Initialize an empty Gemfile: `bundle init`
   2. Add `gem "github-pages", "~> GITHUB-PAGES-VERSION", group: :jekyll_plugins` to the Gemfile
   3. Replace `GITHUB-PAGES-VERSION` with the latest supported version of the `github-pages` gem. You can find this version at [Dependency versions](https://pages.github.com/versions/).
   4. Install the Gemfile: `bundle install`
   5. Serve the website using the command given earlier: `bundle exec jekyll serve`
9. Open the newly added PORTS tab next to your terminal: open the link at port 4000 to view the website

## References

- [GitHub Codespaces with GitHub Pages](https://www.youtube.com/watch?v=8KwoKgYz85k)
- [GitHub Devcontainers - Images](https://github.com/devcontainers/images/tree/main/src/jekyll)
- [Creating a GitHub Pages site with Jekyll](https://docs.github.com/en/pages/setting-up-a-github-pages-site-with-jekyll/creating-a-github-pages-site-with-jekyll)