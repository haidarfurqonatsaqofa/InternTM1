# Simulator Robot Striker

Simulasi berbasis C++ untuk robot *striker* yang bernavigasi pada lapangan grid (9m x 6m) menggunakan siklus **Sense-Think-Act** dan arsitektur **Finite State Machine (FSM)**.

---

# Siklus Utama (Sense - Think - Act)

Setiap *tick* simulasi menjalankan alur berikut:
1. **Sense**: Kamera memindai lapangan untuk mendeteksi koordinat bola.
2. **Think**: FSM menentukan status (*state*) robot berdasarkan persepsi lingkungan.
3. **Act**: Robot mengeksekusi gerakan fisik (berjalan atau menendang bola).

---

# Logika Finite State Machine (FSM)

Perilaku robot diatur oleh 4 *state* utama:

* **SearchState**
  * Robot melakukan penyisiran *serpentine* (zigzag) di lapangan.
  * Jarak belokan ke samping diatur secara presisi sejauh **0.5 meter**.
  * Berpindah ke `ApproachState` saat bola terdeteksi oleh kamera.

* **ApproachState**
  * Mengalkulasi koordinat bola $(X_b, Y_b)$ dan jalur tembak ke gawang lawan $(4.5, 0.0)$.
  * Menentukan titik berdiri ideal di belakang bola:
    $$X_{target} = X_b - 0.5 \cdot \cos(\theta_{gawang})$$
    $$Y_{target} = Y_b - 0.5 \cdot \sin(\theta_{gawang})$$
  * Robot bernavigasi langsung menuju titik target tersebut (diizinkan melintasi koordinat bola jika sejalur).
  * Berpindah ke `AlignState` saat berada di titik target ($\le 0.2\text{m}$).

* **AlignState**
  * Mengunci orientasi tubuh robot agar menghadap presisi ke gawang lawan ($0^\circ$).
  * Berpindah langsung ke `KickState`.

* **KickState**
  * Mengeksekusi tendangan fisik ke bola.
  * Mereset ingatan persepsi bola (`perceivedBallPos = nullopt`).
  * Kembali ke `SearchState` untuk siap memproses bola berikutnya (*auto-respawn*).

---

# Cara Kompilasi & Menjalankan

Jalankan perintah berikut di terminal PowerShell:

```powershell
g++ -std=c++17 -Iinclude (Get-Item src/*.cpp) -o simulator_ichiro
.\simulator_ichiro.exe
