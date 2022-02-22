import { EnvUtils } from '../env_utils';
import '../common/log4js';
import { ConfigUtils } from './config_utils';

function runtimeInit() {
    ConfigUtils.loadByEnv(EnvUtils.env);
}

runtimeInit();
