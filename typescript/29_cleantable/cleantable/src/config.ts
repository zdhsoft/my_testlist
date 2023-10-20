export const config = {
    // database: 'zszh_tiny',
    database: 'xnlr',
    host: 'localhost',
    port: 3306,
    user: 'game',
    password: 'game123',
};

interface xxx {
    name: string;

}

interface xxx {
    sex: boolean;
}

export class k implements xxx {
    name: string;
    sex: boolean;

    public toString() {
        return {
            n: this.name,
            s: this.sex,
        }
    }
}