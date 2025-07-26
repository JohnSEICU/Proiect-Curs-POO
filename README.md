# 🧩 Escape Room Quiz Game – C++ Terminal Adventure

A terminal-based escape room game built with C++, where players solve quiz-style questions, navigate between rooms, and manage limited health and time to escape before the clock runs out. Built as part of the **Erasmus+ Project** by students of the **University POLITEHNICA Bucharest**.

---

## 🎮 Gameplay Overview

- 🧠 Players must answer questions to progress through "rooms"
- ⏳ 60-minute countdown timer to finish the game
- 💔 3 lives (wrong answers reduce health)
- 🗂 Multiple save slots (3) to resume later
- 🗺 Each room includes exits to other rooms
- 💡 Hints are provided only on the first wrong attempt

---

## 🛠 Features

- 🧩 Rooms loaded from `questions.csv`
- ✅ Real-time timer using `std::chrono`
- 💾 Save system across 3 slots (`save1.csv`, `save2.csv`, etc.)
- ⌛ Graceful game over if health reaches 0 or time runs out
- 📝 Game data saved per session
- 📄 Room info includes:
  - Question
  - Correct answer
  - Hint
  - List of valid exits
  - Completion status
  - Is-final-room flag

---

## 🗂 File Structure

```plaintext
project/
├── main.cpp                 # Main game logic and menu
├── questions.csv            # Room/question definitions
├── save1.csv / save2.csv    # Save slot 1–3 (room states)
├── save_room_1.csv          # Room position per save
├── ...
