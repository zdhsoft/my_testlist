"use strict";
exports.__esModule = true;
var env_utils_1 = require("../env_utils");
require("../common/log4js");
var config_utils_1 = require("./config_utils");
function runtimeInit() {
    config_utils_1.ConfigUtils.loadByEnv(env_utils_1.EnvUtils.env);
}
runtimeInit();
