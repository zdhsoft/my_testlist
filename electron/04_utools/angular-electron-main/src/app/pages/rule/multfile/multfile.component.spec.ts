import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MultfileComponent } from './multfile.component';

describe('MultfileComponent', () => {
  let component: MultfileComponent;
  let fixture: ComponentFixture<MultfileComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ MultfileComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(MultfileComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
