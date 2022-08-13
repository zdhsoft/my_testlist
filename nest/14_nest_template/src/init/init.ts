import { XEnvUtils } from '../env_utils';
import '../common/log4js';
import { XConfigUtils } from './config_utils';

function runtimeInit() {
    XConfigUtils.loadByEnv(XEnvUtils.env);
}

runtimeInit();
