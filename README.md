
gcc test.c -o test

gcc infix_to_parentheses_visualizer.c -o infix_to_parentheses_visualizer; ./infix_to_parentheses_visualizer.exe

gcc infix_to_parentheses_visualizer_self.c -o infix_to_parentheses_visualizer_self; ./infix_to_parentheses_visualizer_self.exe

gcc infix_to_parentheses_visualizer_self2.c -o infix_to_parentheses_visualizer_self2; ./infix_to_parentheses_visualizer_self2.exe



gcc infix_to_parentheses_linkedlist.c -o infix_to_parentheses_linkedlist; ./infix_to_parentheses_linkedlist.exe



# 堆疊應用與算式解析：LeetCode 相關題目推薦

這份清單整理了與**中序算式解析（Infix Parsing）**及**優先權運算（Operator Precedence）**邏輯相關的經典 LeetCode 題目。

## 1. 基礎概念：符號與括號處理
這類題目練習如何利用堆疊的 **LIFO（後進先出）** 特性來處理成對的符號。

* **LeetCode 20. Valid Parentheses (Easy)**
    * **核心關聯**：Stack 入門題。練習「遇到結束符號時，檢查堆疊頂端是否有對應起始符號」的邏輯。這與處理括號化時的「成對封裝」邏輯相似。
* **LeetCode 1021. Remove Outermost Parentheses (Easy)**
    * **核心關聯**：練習對括號層級（Depth）的掌控與解析。



---

## 2. 進階應用：算式解析與計算（最相關）
這組題目的邏輯與中序轉括號算式幾乎一致，差別在於要求產出「計算結果」而非「字串」。

* **LeetCode 150. Evaluate Reverse Polish Notation (Medium)**
    * **核心關聯**：處理**後序表達式 (Postfix)**。此題即為 `applyOperator` 邏輯的直接應用：從堆疊彈出兩個數字，運算後將結果推回。
* **LeetCode 227. Basic Calculator II (Medium) ⭐ 最推薦**
    * **核心關聯**：處理包含 `+`, `-`, `*`, `/` 的算式，並實作**運算優先權**。其核心 `while` 判斷邏輯與中序解析演算法完全相同。
* **LeetCode 224. Basic Calculator (Hard)**
    * **核心關聯**：在 Basic Calculator II 的基礎上加入了 **括號 `()`** 的處理。涉及如何在堆疊中處理優先權的「暫停」與「恢復」。



---

## 3. 演算法模型：中序轉其他形式
這類題目考察如何將中序算式（Infix）轉換為不同的資料結構。

* **LeetCode 772. Basic Calculator III (Hard - Premium)**
    * **核心關聯**：綜合了括號與四則運算，是算式解析問題的終極版本。
* **LeetCode 1597. Build Binary Expression Tree from Infix Expression (Hard - Premium)**
    * **核心關聯**：將中序算式轉為**二元表達樹 (Binary Expression Tree)**。其堆疊操作邏輯與字串括號化（將結果封裝進節點）是完全互通的。

---

## 關鍵觀念對照表

| 您的 C 程式碼邏輯 | LeetCode 考察知識點 |
| :--- | :--- |
| `while (getPrecedence(...) >= token)` | **調度場演算法 (Shunting-yard Algorithm)**：決定運算子何時該結算。 |
| `operandStack[(*opnTop)--]` | **LIFO 取值**：確保操作數（Operand）的左、右順序符合運算定義。 |
| `sprintf(newExpr, "(%s%c%s)")` | **表達式重組**：將局部運算結果合併為更大型的結構。 |
| `while (optTop != -1)` | **末尾清理 (Final Flush)**：處理掃描完後堆疊內剩餘的運算任務。 |

