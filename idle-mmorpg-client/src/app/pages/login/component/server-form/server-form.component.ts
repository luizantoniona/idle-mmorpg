import { Component, inject, OnInit } from '@angular/core';
import { FormBuilder, ReactiveFormsModule, FormGroup, Validators } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { InputFieldComponent } from '../../../../component/input-field/input-field.component';
import { ButtonComponent } from '../../../../component/button/button.component';
import { StatusCircleComponent } from '../../../../component/status-circle/status-circle.component';
import { APIService } from '../../../../service/api.service';
import { ServerService } from '../../../../service/server.service';
import { PanelHorizontalComponent } from "../../../../component/panel/panel-horizontal.component";

@Component({
  selector: 'app-server-form',
  templateUrl: './server-form.component.html',
  styleUrls: ['./server-form.component.scss'],
  standalone: true,
  imports: [
    PanelHorizontalComponent,
    StatusCircleComponent,
    InputFieldComponent,
    ButtonComponent,
    ReactiveFormsModule,
    CommonModule
  ]
})
export class ServerFormComponent implements OnInit {
  private fb = inject(FormBuilder);
  private apiService = inject(APIService);
  private serverService = inject(ServerService);

  form: FormGroup;
  status: 'online' | 'offline' | 'loading' | 'error' | 'unknown' = 'offline';
  error: string | null = null;

  constructor() {
    const server = this.serverService.getServer();
    this.form = this.fb.group({
      ip: [server?.address || '', Validators.required],
      port: [server?.port || '', Validators.required],
    });

    if (server) {
      this.status = 'loading';
    }
  }

  ngOnInit(): void {
    if (this.serverService.getServer()) {
      this.checkStatus();
    }
  }

  async checkStatus(): Promise<void> {
    try {
      await this.apiService.getStatus();
      this.status = 'online';
    } catch {
      this.status = 'error';
    }
  }

  async checkStatusWithParams(ip: string, port: string): Promise<boolean> {
    try {
      const cleanedIp = ip.replace(/^https?:\/\//, '');
      const response = await fetch(`http://${cleanedIp}:${port}/status`);
      if (!response.ok) throw new Error();
      this.status = 'online';
      return true;
    } catch {
      this.status = 'error';
      return false;
    }
  }

  async handleSubmit(): Promise<void> {
    this.error = null;
    this.status = 'loading';

    const { ip, port } = this.form.value;
    const ok = await this.checkStatusWithParams(ip, port);

    if (!ok) {
      this.error = 'Could not connect to the server.';
      return;
    }

    this.serverService.connect(ip, port);
  }
}
