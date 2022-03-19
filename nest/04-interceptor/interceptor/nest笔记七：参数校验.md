# nest笔记七：参数校验
nestjs的参数校验官方文档：https://docs.nestjs.com/techniques/validation。 它主要使用第三方的class-validator来进行参数校验。

## Validator-Pipe实现

- 网上给了很多例子，基本上可以直接拿来使用了，下面的这个是我做了一下处理的
```typescript
import { Injectable, PipeTransform, ArgumentMetadata, ValidationError, HttpException, HttpStatus } from '@nestjs/common';
import { plainToClass } from 'class-transformer';
import { validate } from 'class-validator';

/**
 * 这是一个全局的参数验证管道，基于class-transformer
 * 如果失败，则会抛出HttpException
 * 在main.ts的nestApp要将它设为全局的
 */

@Injectable()
export class ValidationPipe implements PipeTransform {
    async transform(value: any, { metatype }: ArgumentMetadata) {
        if (!metatype || !this.toValidate(metatype)) {
            return value;
        }
        const object = plainToClass(metatype, value);
        const errors = await validate(object);
        const errorList: string[] = [];
        const errObjList: ValidationError[] = [...errors];

        do {
            const e = errObjList.shift();
            if (!e) {
                break;
            }
            if (e.constraints) {
                for (const item in e.constraints) {
                    errorList.push(e.constraints[item]);
                }
            }
            if (e.children) {
                errObjList.push(...e.children);
            }
        } while (true);
        if (errorList.length > 0) {
            throw new HttpException('请求参数校验错误:' + errorList.join(), HttpStatus.INTERNAL_SERVER_ERROR);
        }
        return object;
    }

    private toValidate(metatype: Function): boolean {
        const types: Function[] = [String, Boolean, Number, Array, Object];
        return !types.includes(metatype);
    }
}

```

- 然后在app初始化，设置全局的pipe
```typescript
    const app = await NestFactory.create<NestExpressApplication>(AppModule, {
        logger: new NestLogger(),
    });
    app.useGlobalPipes(new ValidationPipe());  //加在这里
    app.useGlobalInterceptors(new RequestInterceptor());
    app.useGlobalFilters(new HttpFilterFilter());
    app.useGlobalGuards(new AuthGuard());
```

## 参数校验的装饰器
- 主要通用，数字相关的，类型相关的，日期相关的，字符串相关的，数组相关，对象相关的几组，见下表
### 通用装饰器
|修饰器	|描述|
|:---|:---|
|@IsDefined(value: any)	|	检查是否定义了值 (!== undefined, !== null)。这是唯一忽略skipMissingProperties选项的装饰程序	|
|@IsOptional()	|	检查给定值是否为空(=== null, === undefined) ，如果是，则忽略属性上的所有验证程序	|
|@Equals(comparison: any)	|	检查值是否相等（“===”）比较	|
|@NotEquals(comparison: any)	|	检查值是否不相等（“!==”）比较	|
|@IsEmpty()	|	检查给定值是否为空(=== ‘’, === null, === undefined)	|
|@IsNotEmpty()	|	检查给定值是否不为空 (!== ‘’, !== null, !== undefined)	|
|@IsIn(values: any[])	|	检查值是否在允许值的数组中	|
|@IsNotIn(values: any[])	|	检查值是否不在不允许的值数组中	|

### 类型验证装饰器
|	修饰器	|	描述	|
|:---|:---|
|@IsBoolean()	|	是否为布尔值	|
|@IsDate()	|	是否为日期	|
|@IsString()	|	是否为字符串	|
|@IsNumber(options: IsNumberOptions)	|	是否为数字	|
|@IsInt()	|	是否为整数	|
|@IsArray()	|	是否为数组	|
|@IsEnum(entity: object)	|	是否是有效的枚举	|

### 数字验证装饰器
|	修饰器	|	描述|
|:---|:---|
|@IsDivisibleBy(num: number)	|	是否是可以被另一个数整除的数	|
|@IsPositive()	|	是否是大于0的整数	|
|@IsNegative()	|	是否是小于0的整数	|
|@Min(min: number)	|	是否大于等于给定的数	|
|@Max(max: number)	|	是否小于等于给定的数	|

### 日期验证装饰器
|	修饰器	|	描述|
|:---|:---|
|@MinDate(date: Date)	|	是否在指定日期之后	|
|@MaxDate(date: Date)	|	是否在指定日期之前	|

### 字符串类型验证装饰器
|	修饰器	|	描述	|
|:---|:---|
|@IsBooleanString()	|	是否为布尔值（例如“true”或“false”）	|
|@IsDateString()	|@IsISO8601（）的别名	|
|@IsNumberString(options?: IsNumericOptions)	|	检查字符串是否为数字	|

### 字符串验证装饰器
|	修饰器	|	描述	|
|:---|:---|
|@Contains(seed: string)	|	是否包含种子	|
|@NotContains(seed: string)	|	是否不包含种子	|
|@IsAlpha()	|	是否只包含字母	|
|@IsAlphanumeric()	|	是否只包含字母和数字	|
|@IsDecimal(options?: IsDecimalOptions)	|	是否为有效的十进制值。默认的IsDecimalOptions是force_decimal=False，decimal_digits:‘1’，locale:‘en-US’	|
|@IsAscii()	|	是否只包含ASCII字符	|
|@IsBase32()	|	是否是base32编码的	|
|@IsBase64()	|	是否是base64编码的	|
|@IsIBAN()	|	是否为IBAN（国际银行帐号）	|
|@IsBIC()	|	是BIC（银行识别码）还是SWIFT码	|
|@IsByteLength(min: number, max?: number)	|	长度（以字节为单位）是否在某个范围内	|
|@IsCreditCard()	|	是否为信用卡	|
|@IsCurrency(options?: IsCurrencyOptions)	|	是否为有效的货币金额	|
|@IsEthereumAddress()	|	是否是以太坊地址。不验证地址校验和	|
|@IsBtcAddress()	|	是否为有效的BTC地址	|
|@IsDataURI()	|	是否为数据uri格式	|
|@IsEmail(options?: IsEmailOptions)	|	是否为电子邮件	|
|@IsFQDN(options?: IsFQDNOptions)	|	是否是完全限定的域名（例如domain.com）	|
|@IsFullWidth()	|	是否包含任何全角字符	|
|@IsHalfWidth()	|	是否包含任何半角字符	|
|@IsVariableWidth()	|	是否包含全半角字符	|
|@IsHexColor()	|	是否为十六进制颜色	|
|@IsHSLColor()	|	是否是基于CSS Colors Level 4规范的HSL颜色	|
|@IsRgbColor(options?: IsRgbOptions)	|	是rgb还是rgba颜色	|
|@IsIdentityCard(locale?: string)	|	是否是有效的身份证代码（估计是国外的身份证格式）	|
|@IsPassportNumber(countryCode?: string)	|	是否是相对于特定国家代码的有效护照号码	|
|@IsPostalCode(locale?: string)	|	是否是邮政编码	|
|@IsHexadecimal()	|	是否为十六进制数	|
|@IsOctal()	|	是否为八进制数	|
|@IsMACAddress(options?: IsMACAddressOptions)	|	是否为MAC地址	|
|@IsIP(version?: "4"\|"6")	|	是否为IP（版本4或6）	|
|@IsPort()	|	是否为有效的端口号	|
|@IsISBN(version?: "10"\|"13")	|	是否为ISBN（版本10或13）	|
|@IsEAN()	|	是否为EAN（欧洲商品编号）	|
|@IsISIN()	|	是否为ISIN（股票/安全标识符）	|
|@IsISO8601(options?: IsISO8601Options)	|	是否为有效的ISO 8601日期格式。对于有效日期的其他检查，请使用选项strict=true。	|
|@IsJSON()	|	是否为有效的JSON	|
|@IsJWT()	|	是否为有效的JWT	|
|@IsLowercase()	|	是否为小写	|
|@IsLatLong()	|	是否为lat，long格式的有效经纬度坐标	|
|@IsLatitude()	|	检查字符串或数字是否是有效的纬度坐标	|
|@IsLongitude()	|	检查字符串或数字是否为有效的经度坐标	|
|@IsMobilePhone(locale: string)	|	是否是移动电话号码	|
|@IsISO31661Alpha2()	|	是否是有效的iso3166-1alpha-2官方指定的国家代码。	|
|@IsISO31661Alpha3()	|	是否是有效的iso3166-1alpha-3官方指定的国家代码。	|
|@IsLocale()	|	是否为区域设置	|
|@IsPhoneNumber(region: string)	|	是否是有效的电话号码	|
|@IsMongoId()	|	是否是MongoDB ObjectId的有效十六进制编码表示形式	|
|@IsMultibyte()	|	是否包含一个或多个多字节字符	|
|@IsNumberString(options?: IsNumericOptions)	|	是否包含任何代理项对字符	|
|@IsSurrogatePair()	|	是否包含任何代理项对字符	|
|@IsUrl(options?: IsURLOptions)	|	是否为url	|
|@IsMagnetURI()	|	是否为magneturi格式	|
|@IsUUID(version?: "3"\|"4"\|"5"\|"all")	|	是否是UUID（version 3、4、5或all）	|
|@IsFirebasePushId()	|	是否为Firebase Push ID	|
|@IsUppercase()	|	是否为大写	|
|@Length(min: number, max?: number)	|	符串的长度是否在某个范围内	|
|@MinLength(min: number)	|	字符串的长度是否不小于给定的数字	|
|@MaxLength(max: number)	|	字符串的长度是否不大于给定的数字	|
|@Matches(pattern: RegExp, modifiers?: string)	|	是否与模式匹配，匹配（‘foo’，/foo/i）或匹配（‘foo’，‘foo’，‘i’）	|
|@IsMilitaryTime()	|	是否是HH:MM格式的有效军事时间表示形式	|
|@IsHash(algorithm: string)	|	是否是散列，以下类型是supported:md4、md5、sha1、sha256、sha384、sha512、ripemd128、ripemd160、tiger128、tiger128、tiger192、crc32、crc32b。	|
|@IsMimeType()	|	是否与有效的MIME类型格式匹配	|
|@IsSemVer()	|	是否为语义版本控制规范（SemVer）	|
|@IsISSN(options?: IsISSNOptions)	|	是否为ISSN	|
|@IsISRC()	|	是否为ISRC	|
|@IsRFC3339()	|	是否为有效的RFC 3339日期	|


### 数组验证装饰器
|	修饰器	|	描述	|
|:---|:---|
|@ArrayContains(values: any[])	|	是否包含给定值数组中的所有值	|
|@ArrayNotContains(values: any[])	|	是否不包含任何给定值	|
|@ArrayNotEmpty()	|	是否为空	|
|@ArrayMinSize(min: number)	|	数组的长度是否大于或等于指定的数字	|
|@ArrayMaxSize(max: number)	|	数组的长度是否小于或等于指定的数字	|
|@ArrayUnique(identifier?: (o) => any)	|	所有数组的值是否唯一。对象的比较是基于引用的。可选函数可以指定用于比较的返回值	|

### 其他验证装饰器
|	修饰器	|	描述	|
|:---|:---|
|@IsInstance(value: any)	|	属性是否是传递值的实例	|
|@Allow()	|	防止在没有为属性指定其他约束时剥离该属性	|
|@ValidateNested()|用这个装饰器标记的对象/对象数组也将被验证。|
|@ValidateIf((object: any, value: any) => boolean)|当提供的条件函数返回 false 时，忽略属性上的其他验证器。|
|@ValidatePromise()|Resolve promise before validation, 这个做为请求参数校验，用不到|
|@IsObject()	|	是否为有效对象（null、函数、数组将返回false）	|
|@IsNotEmptyObject()	|	对象是否为空	|

## DTO 与VO
在 Spring 中，DTO 是 Data Transform Object，即数据传输对象，VO 是 View Object，即视图对象。
目前这里把 DTO 作为入参使用，而 VO 则作为返回值使用

## 传入参数实例
### 一个分页的DTO
```typescript
export class PageDTO {
    @IsInt({ message: '参数pageSize要求是整数!' })
    @Min(1, { message: '参数pageSize最小值是1' })
    @Max(1000, { message: '参数pageSize最大值是1000' })
    pageSize: number;

    @IsInt({ message: '参数pageNo要求是整数!' })
    @Min(1, { message: '参数pageNo的值从1开始' })
    pageNo: number;
}

```
### DTO的派生
- 参数校验，派生的也是有效的
```typescript
class StudentQueryDTO extends PageDTO {
    @IsString({ message: '参数grade要求是字符串!' })
    @Length(1, 30, { message: '参数grade的长度范围是1,30' })
    grade: string;
}
```
### 某个controller调用，验证参数
- 使用@Body这个注入后，就可以验证参数
```typescript
Controller('/grade')
class GradeController {
	@Post('list')
	async gradeList(@Body() param: StudentQueryDTO) {
		// ...  
	}
}
```

### message的标志信息
- 在上面的例子中，pageSize是一个被校验的数据成员的名称，很多相同的校验，这块是相同的。仅是名称不同
- 在validator中有提供一组‘$’开头的标志，用于替换特定的值
如下面这段：
```typescript
{ message: '参数pageSize要求是整数!' }
```
替换后
```typescript
{ message: '参数$property要求是整数!' }
```
#### 校验定义的参数接口定义如下

```typescript
/**
 * Arguments being sent to message builders - user can create message either by simply returning a string,
 * either by returning a function that accepts MessageArguments and returns a message string built based on these arguments.
 */
export interface ValidationArguments {
    /**
     * Validating value.
     */
    value: any;
    /**
     * Constraints set by this validation type.
     */
    constraints: any[];
    /**
     * Name of the target that is being validated.
     */
    targetName: string;
    /**
     * Object that is being validated.
     */
    object: object;
    /**
     * Name of the object's property being validated.
     */
    property: string;
}
```

#### 下面的代码是替换过程 如下
```typescript
import { ValidationArguments } from './ValidationArguments';

/**
 * Convert the constraint to a string to be shown in an error
 */
export function constraintToString(constraint: unknown): string {
  if (Array.isArray(constraint)) {
    return constraint.join(', ');
  }

  return `${constraint}`;
}

export class ValidationUtils {
  static replaceMessageSpecialTokens(
    message: string | ((args: ValidationArguments) => string),
    validationArguments: ValidationArguments
  ): string {
    let messageString: string;
    if (message instanceof Function) {
      messageString = (message as (args: ValidationArguments) => string)(validationArguments);
    } else if (typeof message === 'string') {
      messageString = message;
    }

    if (messageString && Array.isArray(validationArguments.constraints)) {
      validationArguments.constraints.forEach((constraint, index) => {
        messageString = messageString.replace(
          new RegExp(`\\$constraint${index + 1}`, 'g'),
          constraintToString(constraint)
        );
      });
    }

    if (
      messageString &&
      validationArguments.value !== undefined &&
      validationArguments.value !== null &&
      typeof validationArguments.value === 'string'
    )
      messageString = messageString.replace(/\$value/g, validationArguments.value);
    if (messageString) messageString = messageString.replace(/\$property/g, validationArguments.property);
    if (messageString) messageString = messageString.replace(/\$target/g, validationArguments.targetName);

    return messageString;
  }
}
```


#### 从上面代码中，可以看出来校验替换的标志只有几个
|标志|参数字段名称|说明|
|:---|:---|:---|
|$property|validationArguments.property|the value that is being validated|
|$target|validationArguments.targetName|name of the object's property being validated|
|$value|validationArguments.value|name of the object's class being validated|
|$constraint1|validationArguments.constraints[0]|constraints defined by specific validation type|
|$constraint2|validationArguments.constraints[1]||
|$constraint3|validationArguments.constraints[2]||
|...|...|...|
|$constraintN|validationArguments.constraints[n-1]||

#### 重新定义的PageDTO
```typescript
export class PageDTO {
    @IsInt({ message: '参数$property要求是整数!, 您输入的值是:$value' })
    @Min(1, { message: '参数$property最小值是1, 您输入的值是:$value' })
    @Max(1000, { message: '参数$property最大值是1000, 您输入的值是:$value' })
    pageSize: number;

    @IsInt({ message: '参数pageNo要求是整数!' })
    @Min(1, { message: '参数pageNo的值从1开始' })
    pageNo: number;
}
```
## 自定义校验装饰器
- 现有的参数装饰器还不能完全满足要求，例如：要入传入的数组中的所有元素都是整数，下面是实现的代码
- 装饰器的例子，可以参考class-validator源代码
```typescript
import { buildMessage, ValidateBy, ValidationOptions } from 'class-validator';

export const ARRAY_IS_ALL_INTEGER = 'ArrayIsAllInt';

/** 检查数组中每个元素是不是都是整数 */
function checkArrayElementInteger(array: unknown[]): boolean {
    if (!Array.isArray(array)) return false;
    for (const v of array) {
        if (!Number.isInteger(v)) {
            return false;
        }
    }
    return true;
}

/**
 * 检查数组中每个元素是不是都是整数.
 */
export function ArrayIsAllInt(validationOptions?: ValidationOptions): PropertyDecorator {
    const options = validationOptions;
    return ValidateBy(
        {
            name: ARRAY_IS_ALL_INTEGER,
            validator: {
                validate: (value, args): boolean => checkArrayElementInteger(value),
                defaultMessage: buildMessage(
                    (eachPrefix) => eachPrefix + "$property's a non-integer in the array",
                    options,
                ),
            },
        },
        options,
    );
}

```
- 下面是使用实例
```typescript
class DTOTest {
    @IsArray({ message: '$property要求是数组!' })
    @ArrayIsAllInt({ message: '存在非整数的元素:$property' })
    public id: number[];
}
```
## 疑问
- 被校验的参数不是基本数据类型的时候，使用@ValidateNested()
- 默认的情况下，不会跳过未定义的属性，除非在pipe中调用validator函数，指定了skipUndefinedProperties = true 
- 对于非必传的参数，可以使用@IsOptional

## 相关文章列表
- [nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)

