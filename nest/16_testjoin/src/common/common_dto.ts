import { IsInt, Max, Min } from 'class-validator';

export class XPageDTO {
    @IsInt({ message: '参数page_size要求是整数!' })
    @Min(1, { message: '参数page_size最小值是1' })
    @Max(1000, { message: '参数page_size最大值是1000' })
    page_size!: number;

    @IsInt({ message: '参数page_no要求是整数!' })
    @Min(1, { message: '参数page_no的值从1开始' })
    page_no!: number;
}
