import { IsInt, Max, Min } from 'class-validator';

export class XPageDTO {
    @IsInt({ message: '参数pageSize要求是整数!' })
    @Min(1, { message: '参数pageSize最小值是1' })
    @Max(1000, { message: '参数pageSize最大值是1000' })
    pageSize: number;

    @IsInt({ message: '参数pageNo要求是整数!' })
    @Min(1, { message: '参数pageNo的值从1开始' })
    pageNo: number;
}
