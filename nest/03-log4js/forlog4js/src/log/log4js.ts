export class XLogManager {
    private static m_instance = new XLogManager();
    public static getInstance() {
        return this.m_instance;
    }
    private constructor() {

    }
};
