
# Performance Benchmark Plan

## 1. Objective

Measure whether Serpantinum Native improves resource
usage compared with the original shell.

Primary goals:
- Reduce idle memory usage.
- Keep CPU usage low when idle.
- Maintain responsive animations and interactions.
- Avoid sacrificing essential functionality.

## 2. Test Environment

- OS: CachyOS Linux
- Compositor: Hyprland
- CPU: Intel Core i5-1135G7
- RAM: 8 GB
- GPU: Intel Iris Xe

Record before testing:
- Kernel version
- Hyprland version
- Shell version
- UI toolkit version
- Display resolution and refresh rate
- Enabled shell features
- Background applications

## 3. Measurements

### Memory
- Process RSS in KiB
- Total system memory used
- Memory after startup
- Memory after five minutes idle
- Memory with common features active

### CPU
- Idle CPU usage
- CPU usage during interactions
- CPU usage during animations
- Startup CPU activity

### Responsiveness
- Startup time
- Time to open the launcher
- Time to switch workspaces
- UI stuttering or missed updates

### Stability
- Startup failures
- Crashes
- Recovery after restart
- Suspend and resume behavior

## 4. Test Conditions

- Use the same machine and display setup.
- Keep background applications consistent.
- Use equivalent features in both shells.
- Allow startup activity to settle.
- Repeat measurements several times.
- Record results rather than relying on impressions.

## 5. Benchmark Results

No measurements recorded yet.

| Shell | Scenario | RSS | CPU | Notes |
|---|---|---|---|---|
| Noctalia v5 | Idle | TBD | TBD | Baseline pending |
| Serpantinum | Idle | TBD | TBD | To be measured |
| Native prototype | Idle | TBD | TBD | Not implemented |

## 6. Interpretation

RSS measures resident memory used by a process.
It does not equal total system memory usage.

Compare both process memory and overall system memory.
Account for shared libraries and other background services.

A lower RAM number alone does not prove better performance.
Responsiveness, stability, and feature parity also matter.

## 7. Optimization Rules

- Measure before changing code.
- Change one major factor at a time.
- Avoid unnecessary background polling.
- Prefer event-driven updates when practical.
- Avoid unnecessary processes and dependencies.
- Re-measure after each meaningful optimization.

## Current Status

Benchmarking has not started.
No performance claims have been verified.


### Baseline Noctalia — 22 Oktober 2026

- Sistem: CachyOS + Hyprland
- RAM fisik: 8 GB (7,5 GiB terdeteksi)
- Proses Noctalia: PID 1047
- RSS awal: 134928 KiB
- RSS pengukuran berulang: 132476–132728 KiB
- Rata-rata RSS berulang: sekitar 129,6 MiB
- CPU pengukuran berulang: sekitar 1,1%
- Jumlah sampel: 5
- Kondisi: sesi ketika Arknights sedang diluncurkan; kondisi game belum dipastikan stabil.

Catatan: RSS adalah memori resident proses, bukan total penggunaan
memori seluruh komponen shell. Hasil CPU merupakan sampel sesaat.
