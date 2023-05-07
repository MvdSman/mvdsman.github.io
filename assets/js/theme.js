// Ref: https://derekkedziora.com/blog/dark-mode-revisited

function prefersColorTest(systemInitiatedDark) {
    if (systemInitiatedDark.matches) {
        document.documentElement.setAttribute('data-theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Theme";
        // this clears the session storage 
        sessionStorage.setItem('theme', '');
    } else {
        document.documentElement.setAttribute('data-theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Theme";
        sessionStorage.setItem('theme', '');
    }
}
systemInitiatedDark.addListener(prefersColorTest);

function modeSwitcher() {
    // it’s important to check for overrides again 
    let theme = sessionStorage.getItem('theme');
    // checks if reader selected dark theme 
    if (theme === "dark") {
        document.documentElement.setAttribute('data-theme', 'light');
        sessionStorage.setItem('theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Theme";
        // checks if reader selected light theme 
    } else if (theme === "light") {
        document.documentElement.setAttribute('data-theme', 'dark');
        sessionStorage.setItem('theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Theme";
        // checks if system set dark theme 
    } else if (systemInitiatedDark.matches) {
        document.documentElement.setAttribute('data-theme', 'light');
        sessionStorage.setItem('theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Theme";
        // the only option left is system set light theme
    } else {
        document.documentElement.setAttribute('data-theme', 'dark');
        sessionStorage.setItem('theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Theme";
    }
}

if (theme === "dark") {
	document.documentElement.setAttribute('data-theme', 'dark');
	sessionStorage.setItem('theme', 'dark');
	document.getElementById("theme-toggle").innerHTML = "Light Theme";
} else if (theme === "light") {
	document.documentElement.setAttribute('data-theme', 'light');
	sessionStorage.setItem('theme', 'light');
	document.getElementById("theme-toggle").innerHTML = "Dark Theme";
}