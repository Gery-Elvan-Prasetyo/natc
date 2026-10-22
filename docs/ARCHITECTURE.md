
# Architecture Plan

## 1. Project Goal

Build a native desktop shell inspired by Serpantinum
for CachyOS and Hyprland.

Primary goals:
- Reduce idle memory usage.
- Keep the interface responsive.
- Reimplement features incrementally.
- Keep the existing desktop configuration safe.

## 2. Reference Project

Upstream: https://github.com/ilyamiro/serpantinum

Serpantinum uses QML and Quickshell, with supporting
scripts and compositor-specific integration.

Its features and dependencies must be audited before
we decide what to reimplement.

## 3. Language Evaluation

### C++
- Candidate for the main application and UI.
- Evaluate Qt 6 and native Wayland integration.
- Measure memory usage and startup time.

### Rust
- Candidate for the main application or system services.
- Evaluate suitable Wayland and UI libraries.
- Measure memory usage and startup time.

Final language decision: Pending.

## 4. Proposed Modules

- Core: application lifecycle and shared state.
- UI: bar, launcher, panels, and popups.
- Hyprland: IPC and workspace integration.
- System: audio, brightness, battery, and network.
- Notifications: display and notification history.
- Settings: themes, configuration, and preferences.
- Diagnostics: logging, performance, and error handling.

## 5. Development Milestones

1. Audit upstream features and dependencies.
2. Record baseline resource usage.
3. Build a minimal native bar.
4. Integrate Hyprland IPC.
5. Implement features incrementally.
6. Test stability and resource usage.
7. Review feature parity and licensing.

## 6. Performance Evaluation

Measure:
- Idle RSS memory.
- Total system memory usage.
- Idle and active CPU usage.
- Startup time.
- UI responsiveness.
- Stability after restart and suspend.

Compare equivalent features under equivalent conditions.

## 7. Safety and Compatibility

- Keep the existing Hyprland configuration unchanged.
- Develop and test in a separate project directory.
- Do not replace the current shell until the new one is stable.
- Review upstream licensing before copying or modifying code.

## 8. Current Status

Planning stage.

No native application code has been implemented.
Language, UI toolkit, and module boundaries remain
subject to technical evaluation.