package utils

// import (
// 	"admin/common/klog"
// 	"context"

// 	"github.com/tealeg/xlsx"
// 	"go.uber.org/zap"
// )

// func BuildXlsx() error {

// 	ctx := context.Background()

// 	// 创建Excel文件对象
// 	file := xlsx.NewFile()

// 	// 创建Excel表格对象
// 	sheet, err := file.AddSheet("Sheet1")
// 	if err != nil {
// 		klog.ErrorContextFields(ctx, "AddSheet file...",
// 			zap.Error(err),
// 		)
// 		return err
// 	}

// 	// 向表格中添加表头信息
// 	header := sheet.AddRow()
// 	// header.SetHeight(20)

// 	cell := header.AddCell()
// 	cell.Value = "姓名"

// 	cell = header.AddCell()
// 	cell.Value = "年龄"

// 	// // 向表格中添加数据行
// 	// data := []struct {
// 	// 	Name string
// 	// 	Age  int
// 	// }{
// 	// 	{"张三", 20},
// 	// 	{"李四", 25},
// 	// 	{"王五", 30},
// 	// }

// 	// for _, item := range data {
// 	// 	row := sheet.AddRow()
// 	// 	row.SetHeight(20)

// 	// 	cell := row.AddCell()
// 	// 	cell.Value = item.Name

// 	// 	cell = row.AddCell()
// 	// 	cell.SetInt(item.Age)
// 	// }

// 	// 保存Excel文件
// 	err = file.Save("report2.xlsx")
// 	if err != nil {
// 		klog.ErrorContextFields(ctx, "Save file...",
// 			zap.Error(err),
// 		)
// 		return err
// 	}

// 	return nil
// }

import (
	"fmt"

	excelize "github.com/xuri/excelize/v2"
)

// 生成excel表格
func TouchExcel() {
	//开启新的文件
	f := excelize.NewFile()

	//创建一个工作表
	index := f.NewSheet("工作表名")

	//设置默认的工作表
	f.SetActiveSheet(index)

	//给单元格赋值
	f.SetCellValue("工作表名", "A2", "hello")
	f.SetCellValue("工作表名", "B2", "100")

	//创建一个工作表
	f.NewSheet("Sheet1")

	f.SetCellValue("Sheet1", "B2", "100")
	//保存路径
	if err := f.SaveAs("test3.xlsx"); err != nil {
		fmt.Println("保存文件失败：", err)
	}
}

// 打开excel,读取数据
func ReadExcel() {
	f, err := excelize.OpenFile("test3.xlsx")
	if err != nil {
		fmt.Println("打开excel文件失败")
	}

	//打开文件后要关闭
	defer f.Close()

	//获取指定单元格的值
	cell, err := f.GetCellValue("Sheet1", "B2")
	if err != nil {
		fmt.Println("获取数据失败：", err)
		return
	}
	fmt.Printf(cell)

	//获取 工作表名 上所有单元格的值
	rows, err := f.GetRows("工作表名")
	if err != nil {
		fmt.Println("获取单元格失败：", err)
		return
	}
	//遍历数组
	for i, row := range rows {
		if i == 0 { //表格第一行常为表头，单独拎出来
			fmt.Println(row) //输出格式：[xxx xxx xxx]
		} else {
			fmt.Println(row[0], row[1]) //可用row[num]来获取单元格里的数据，方便后续使用
		}

	}

	//遍历数组,for循环
	for i := 0; i < len(rows); i++ {
		fmt.Println(rows[i]) //输出格式：[xxx xxx xxx]
	}
}
