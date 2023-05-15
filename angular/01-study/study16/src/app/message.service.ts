import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class MessageService {
  private m_messages: string[] = [];
  constructor() { }
  get messages() {
    return this.m_messages;
  }
  add(paramMsg: string) {
    console.log('msg:' + paramMsg);
    this.m_messages.push(paramMsg);
  }
  clear() {
    this.m_messages = [];
  }
}
