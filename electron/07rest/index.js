var electron = require('electron');
var app = electron.app;
var BrowserView = electron.BrowserView;
var win = null;

app.on('ready', ()=>{
    win = new BrowserView({
        webPreferences: {
            nodeIntegration: true,
        }
    });
    win.loadFile('index.html')
    win.on('closed', function() {
        win = null;
    });
});

app.on('window-all-closed', () => {
    app.quit()
});
