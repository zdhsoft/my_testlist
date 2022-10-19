const { app, BrowserWindow, ipcMain, nativeTheme, Menu, MenuItem } = require('electron');
const path = require('path');

let progressInterval;
const INCREMENT = 0.03;
const INTERVAL_DELAY = 100;
let c = 0;


const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
        }
    })

    win.loadFile('index.html');
    ipcMain.handle('dark-mode:toggle', () => {
        if (nativeTheme.shouldUseDarkColors) {
          nativeTheme.themeSource = 'light'
        } else {
          nativeTheme.themeSource = 'dark'
        }
        return nativeTheme.shouldUseDarkColors
      })

      ipcMain.handle('dark-mode:system', () => {
        nativeTheme.themeSource = 'system'
      })

      progressInterval = setInterval(() => {
        win.setProgressBar(c);
        if (c < 2) {
            c += INCREMENT
        } else {
            c = (-INCREMENT * 5) // reset to a bit less than 0 to show reset state
        }
    }, INTERVAL_DELAY);
    app.on('before-quit', () => {
        clearInterval(progressInterval)
    });

}
app.whenReady().then(() => {
    createWindow()
});




const menu = new Menu()
menu.append(new MenuItem({
  label: 'Electron',
  submenu: [{
    role: 'help',
    accelerator: process.platform === 'darwin' ? 'Alt+Cmd+I' : 'Alt+Shift+I',
    click: () => { console.log('Electron rocks!') }
  }]
}))

Menu.setApplicationMenu(menu)

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit()
})

app.whenReady().then(() => {
    // createWindow()

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) createWindow()
    })
})
