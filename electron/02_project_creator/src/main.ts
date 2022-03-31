/*************************************************************************
 * Copyright(c) 2017-2022,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 zdhsoft       创建文件            2022-03-28
 *************************************************************************/

// const { app, BrowserWindow } = require('electron');
import { app, BrowserWindow } from 'electron';
import path from 'path';
const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        icon: path.join(process.cwd(), 'app.ico'),
        webPreferences: {
            preload: path.join(process.cwd(), 'preload.js'),
        },
    });

    win.loadFile('html/index.html');
};

if (process.platform === 'darwin') {
    app.dock.setIcon(path.join(process.cwd(), './app.ico'));
}

app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) createWindow();
    });
});
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});
