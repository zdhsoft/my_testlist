document.getElementById('toggle-dark-mode').addEventListener('click', async () => {
    const isDarkMode = await window.darkMode.toggle();
    document.getElementById('theme-source').innerHTML = isDarkMode ? 'Dark' : 'Light';
})

document.getElementById('reset-to-system').addEventListener('click', async () => {
    await window.darkMode.system();
    document.getElementById('theme-source').innerHTML = 'System';
})

const t = 'Title';
const b = 'Nofification from the renderer process. click to log to console.';
const m = 'notification clicked!';
new Notification(t, {body: b}).click = () => document.getElementById('output').innerText = m;
