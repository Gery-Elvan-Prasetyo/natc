
# Development Roadmap

Project: Serpantinum Native
Platform: CachyOS + Hyprland
Primary goal: Native desktop shell with efficient resource usage.

## Phase 0 — Project Preparation

- [x] Create project directory
- [x] Create README.md
- [x] Create feature inventory
- [x] Create architecture plan
- [ ] Complete this roadmap
- [ ] Audit upstream features and dependencies
- [ ] Review licensing requirements

Completion criteria:
The project scope and development approach are documented.

## Phase 1 — Baseline and Technology Selection

- [ ] Record current system memory usage
- [ ] Record current shell process usage
- [ ] Compare C++ and Rust UI options
- [ ] Choose a Wayland layer-shell implementation
- [ ] Define the initial build system
- [ ] Document selected dependencies

Completion criteria:
Technology choices are justified and the baseline is recorded.

## Phase 2 — Minimal Native Shell

- [ ] Create the application entry point
- [ ] Create one Wayland bar
- [ ] Display the current time
- [ ] Support basic configuration
- [ ] Add startup and shutdown handling
- [ ] Measure memory and CPU usage

Completion criteria:
The bar works reliably without replacing the existing shell.

## Phase 3 — Hyprland Integration

- [ ] Connect to Hyprland IPC
- [ ] Display workspace information
- [ ] Display the active window
- [ ] Handle workspace changes
- [ ] Handle reconnects and errors

Completion criteria:
Desktop information updates reliably.

## Phase 4 — Core Desktop Features

- [ ] Application launcher
- [ ] Audio controls
- [ ] Brightness controls
- [ ] Network and battery indicators
- [ ] Notification display
- [ ] Control center

Completion criteria:
Each implemented feature works independently and reliably.

## Phase 5 — Appearance and Customization

- [ ] Theme and color configuration
- [ ] Transparency and styling
- [ ] Wallpaper integration
- [ ] Animations
- [ ] User preferences
- [ ] Persistent settings

Completion criteria:
Appearance can be customized without editing source code.

## Phase 6 — Advanced Features

- [ ] Clipboard integration
- [ ] Screenshot integration
- [ ] Notification history
- [ ] Additional panels and widgets
- [ ] Keyboard shortcuts
- [ ] Other audited upstream features

Completion criteria:
Prioritized features have been implemented or documented
as intentionally out of scope.

## Phase 7 — Testing and Optimization

- [ ] Measure idle RSS and system memory usage
- [ ] Measure CPU usage during idle and activity
- [ ] Test startup and shutdown
- [ ] Test suspend and resume
- [ ] Test shell recovery after a crash
- [ ] Test multiple monitors if available
- [ ] Compare against the original under equivalent conditions
- [ ] Fix critical bugs

Completion criteria:
Results are measured, documented, and reproducible.

## Phase 8 — Daily Use

- [ ] Test without removing the existing shell
- [ ] Test login startup in a separate configuration
- [ ] Verify essential desktop functionality
- [ ] Document installation and recovery
- [ ] Decide whether the shell is ready for daily use

Completion criteria:
The new shell is stable enough for the intended environment.

## Project Rules

- Develop in a separate project directory.
- Keep the existing Hyprland configuration safe.
- Avoid unnecessary dependencies.
- Never assume native code automatically uses less RAM.
- Measure before and after optimization.
- Do not copy upstream code without reviewing its license.

## Current Status

Phase 0 — Project preparation.
