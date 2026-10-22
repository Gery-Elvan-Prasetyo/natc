# Upstream Audit — Serpantinum Native

## 1. Tujuan

Dokumen ini mencatat fitur dan perilaku proyek Serpantinum asli yang perlu diperiksa sebelum dibuat ulang menjadi `serpantinum-native`.

Audit ini bukan daftar fitur final. Fitur dapat ditambahkan, diubah prioritasnya, atau ditunda seiring perkembangan proyek.

## 2. Referensi upstream

- Repository: https://github.com/ilyamiro/serpantinum
- Dokumentasi resmi: https://serpantinum.dev/
- Lisensi upstream: GNU AGPL-3.0-or-later
- Tanggal audit awal: 2026-10-22

## 3. Status verifikasi

Gunakan status berikut:

- `Belum diperiksa` — baru kandidat fitur.
- `Perlu diverifikasi` — ada petunjuk di dokumentasi atau changelog.
- `Terverifikasi` — perilaku dan implementasinya sudah diperiksa.
- `Dipertahankan` — disetujui untuk direncanakan di versi native.
- `Ditunda` — belum menjadi prioritas.
- `Tidak diadopsi` — sengaja tidak dimasukkan, dengan alasan.

## 4. Daftar kandidat fitur upstream

Daftar berikut merupakan titik awal audit, bukan jaminan bahwa seluruh detail perilaku sudah diverifikasi.

| Area | Kandidat fitur | Status | Catatan |
|---|---|---|---|
| Desktop shell | Panel/bar dan modul sistem | Perlu diverifikasi | Periksa konfigurasi dan interaksi |
| Navigasi aplikasi | Launcher dan pencarian | Perlu diverifikasi | Periksa pencarian, keyboard, dan hasil |
| Workspace | Informasi dan perpindahan workspace | Perlu diverifikasi | Periksa perilaku tiap compositor |
| Dock | Dock aplikasi | Perlu diverifikasi | Periksa visibilitas dan interaksi |
| System panel | Kontrol dan informasi sistem | Perlu diverifikasi | Audit tiap subfitur |
| Notifikasi | Tampilan dan pengelolaan notifikasi | Perlu diverifikasi | Periksa tindakan dan izin |
| Quick actions | Aksi cepat dan utilitas | Perlu diverifikasi | Inventarisasi fitur satu per satu |
| Widgets | Widget desktop dan pengaturannya | Perlu diverifikasi | Periksa siklus hidup widget |
| Clipboard | Riwayat clipboard | Perlu diverifikasi | Periksa dependensi dan batas penyimpanan |
| Media | Kontrol media dan informasi pemutaran | Perlu diverifikasi | Periksa integrasi MPRIS |
| Lock screen | Layar kunci | Perlu diverifikasi | Prioritaskan audit keamanan |
| Screenshot | Antarmuka tangkapan layar | Perlu diverifikasi | Periksa alur pengambilan dan izin |
| OSD | Indikator volume, brightness, dan status | Perlu diverifikasi | Periksa sumber perubahan status |
| Tema | Warna, tampilan, dan animasi | Perlu diverifikasi | Catat opsi konfigurasi |
| Internasionalisasi | Bahasa dan terjemahan | Perlu diverifikasi | Tentukan kebutuhan bahasa |
| Integrasi compositor | Hyprland, Niri, Sway, dan Mango | Perlu diverifikasi | Periksa dukungan serta batas kompatibilitas |

## 5. Format audit per fitur

Untuk setiap fitur yang diperiksa, catat:

- **Nama fitur:**
- **Referensi sumber:** tautan file, dokumentasi, atau bagian kode upstream.
- **Perilaku yang terlihat oleh pengguna:**
- **Input dan output:**
- **Integrasi sistem yang diperlukan:**
- **Dependensi eksternal:**
- **Perilaku saat dependensi tidak tersedia:**
- **Dampak RAM dan CPU:**
- **Pertimbangan keamanan dan privasi:**
- **Prioritas:** wajib / penting / opsional / eksperimen.
- **Keputusan:** pertahankan / ubah / tunda / tidak diadopsi.
- **Status verifikasi:**

## 6. Prinsip porting ke native

1. Jangan menganggap implementasi native otomatis lebih hemat sumber daya.
2. Ukur baseline sebelum menentukan target optimasi.
3. Pertahankan perilaku penting, bukan sekadar tampilan yang mirip.
4. Hindari menjalankan proses polling atau layanan latar belakang yang tidak diperlukan.
5. Pisahkan komponen inti dari fitur opsional jika desainnya memungkinkan.
6. Tangani kegagalan dependensi tanpa membuat seluruh shell ikut gagal.
7. Uji kompatibilitas berdasarkan compositor dan lingkungan yang benar-benar didukung.
8. Dokumentasikan alasan setiap fitur dipertahankan, diubah, atau ditunda.

## 7. Lisensi dan atribusi

Repository upstream menyatakan lisensi GNU AGPL-3.0-or-later.

Sebelum menyalin atau mengadaptasi kode, aset, maupun bagian implementasi upstream, periksa ketentuan lisensi dan kewajiban atribusinya. Menulis ulang dalam bahasa pemrograman berbeda tidak dengan sendirinya menghilangkan persoalan lisensi.

Status lisensi dan strategi distribusi `serpantinum-native` masih perlu ditinjau sebelum publikasi.

## 8. Keputusan yang belum final

- Bahasa implementasi: Rust atau C++.
- Toolkit antarmuka dan integrasi Wayland.
- Batas fitur inti dan fitur opsional.
- Compositor yang menjadi target pertama.
- Strategi konfigurasi dan kompatibilitas.
- Target performa setelah baseline dan prototipe dapat dibandingkan.

## 9. Langkah audit berikutnya

1. Periksa struktur kode upstream.
2. Verifikasi fitur berdasarkan sumber aslinya.
3. Catat perilaku yang wajib dipertahankan.
4. Cocokkan hasil audit dengan `FEATURES.md` dan `ARCHITECTURE.md`.
5. Perbarui prioritas di `ROADMAP.md` setelah ada cukup bukti.

## 10. Temuan awal dari sumber upstream

### A. Batas tanggung jawab shell

- Serpantinum menyediakan antarmuka desktop.
- Pengelolaan monitor dan keybind compositor bukan tanggung jawab shell.
- Native rewrite harus membedakan fitur shell dengan konfigurasi compositor.

Status: **Terverifikasi dari dokumentasi umum.**

### B. Kompatibilitas compositor

Compositor yang tercantum di repository upstream:

- Hyprland
- Niri
- Sway
- Mango

Status: **Terverifikasi sebagai daftar dukungan upstream; kompatibilitas implementasi native belum diuji.**

### C. Konfigurasi

- Lokasi konfigurasi utama: `~/.config/serpantinum/settings.json`, dengan dukungan `XDG_CONFIG_HOME`.
- Konfigurasi mencakup pengaturan umum, bar, launcher, dock, dan tema.
- Dokumentasi menyebut perubahan konfigurasi langsung diterapkan tanpa reload manual.

Pertimbangan native:
- Sediakan konfigurasi yang terdokumentasi.
- Validasi nilai dan tangani konfigurasi yang tidak valid.
- Pertimbangkan pemuatan ulang konfigurasi tanpa memulai ulang seluruh shell.

Status: **Terverifikasi dari dokumentasi konfigurasi upstream.**

### D. Area fitur untuk audit lanjutan

Kelompok fitur yang perlu diperiksa secara terpisah:

1. Bar dan modul status.
2. Dock dan pelacakan aplikasi berjalan.
3. Launcher dan pencarian aplikasi.
4. Panel sistem, jaringan, audio, Bluetooth, dan daya.
5. Notifikasi dan OSD.
6. Clipboard, screenshot, dan lock screen.
7. Widget, wallpaper, dan tema.
8. Media, kontrol pemutaran, dan visualizer.
9. Quick actions dan pengaturan shell.
10. Integrasi compositor dan layanan eksternal.

Status: **Daftar area audit; bukan pernyataan bahwa setiap detail sudah diverifikasi.**

### E. Sumber audit

- Repository: https://github.com/ilyamiro/serpantinum
- Ikhtisar: https://serpantinum.dev/overview/
- Konfigurasi: https://serpantinum.dev/configure/
- Changelog: https://github.com/ilyamiro/serpantinum/blob/master/CHANGELOG.md

Untuk setiap fitur, catat tautan sumber yang spesifik sebelum menetapkan perilaku dan prioritas porting.

### F. Catatan keputusan

Belum ada keputusan final mengenai bahasa pemrograman, toolkit UI, atau urutan implementasi. Audit ini juga tetap terbuka untuk fitur tambahan yang diusulkan kemudian.

**Catatan:** Dokumen ini bersifat sementara dan boleh direvisi ketika kebutuhan baru ditemukan.
