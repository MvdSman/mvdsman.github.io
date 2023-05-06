function prefersColorTest(systemInitiatedDark) {
    if (systemInitiatedDark.matches) {
        document.documentElement.setAttribute('data-theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Mode";
        // this clears the session storage 
        sessionStorage.setItem('theme', '');
    } else {
        document.documentElement.setAttribute('data-theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Mode";
        sessionStorage.setItem('theme', '');
    }
}
systemInitiatedDark.addListener(prefersColorTest);

function modeSwitcher() {
    // it’s important to check for overrides again 
    let theme = sessionStorage.getItem('theme');
    // checks if reader selected dark mode 
    if (theme === "dark") {
        document.documentElement.setAttribute('data-theme', 'light');
        sessionStorage.setItem('theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Mode";
        // checks if reader selected light mode 
    } else if (theme === "light") {
        document.documentElement.setAttribute('data-theme', 'dark');
        sessionStorage.setItem('theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Mode";
        // checks if system set dark mode 
    } else if (systemInitiatedDark.matches) {
        document.documentElement.setAttribute('data-theme', 'light');
        sessionStorage.setItem('theme', 'light');
        document.getElementById("theme-toggle").innerHTML = "Dark Mode";
        // the only option left is system set light mode
    } else {
        document.documentElement.setAttribute('data-theme', 'dark');
        sessionStorage.setItem('theme', 'dark');
        document.getElementById("theme-toggle").innerHTML = "Light Mode";
    }
}

if (theme === "dark") {
	document.documentElement.setAttribute('data-theme', 'dark');
	sessionStorage.setItem('theme', 'dark');
	document.getElementById("theme-toggle").innerHTML = "Light Mode";
} else if (theme === "light") {
	document.documentElement.setAttribute('data-theme', 'light');
	sessionStorage.setItem('theme', 'light');
	document.getElementById("theme-toggle").innerHTML = "Dark Mode";
}