import { Body, Controller, Post, Request, UseGuards } from '@nestjs/common';
import { AuthService } from 'src/auth/auth.service';
import { LocalGuard } from 'src/local.guard';

@Controller('login')
export class LoginController {
    // constructor(private readonly authService: AuthService) {}
    // @UseGuards(LocalGuard)
    // @Post()
    // async login(@Body() loginUserDto: { username: string; password: string }) {
    //     return await this.authService.validateUser(loginUserDto.username, loginUserDto.password);
    // }
}
