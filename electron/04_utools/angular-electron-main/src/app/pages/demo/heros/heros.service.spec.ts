import { TestBed } from '@angular/core/testing';

import { HerosService } from './heros.service';

describe('HerosService', () => {
  let service: HerosService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(HerosService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
