---
layout: page
title: "Chapter 6: C Programming for Embedded Systems"
parent: Microcontroller Programming
nav_order: 1
---

# C Programming for Embedded Systems

## Table of Contents
{: .no_toc}

1. TOC
{:toc}

---

C programming forms the foundation of embedded systems development. As a systems programming language, C provides an efficient mapping between human-readable code and machine instructions, making it ideal for resource-constrained embedded applications.

{: .note}
The lecture slides used for this section are available [here](./slides/chapter-6-c-programming-slides.pdf).

## Introduction to C for Embedded Applications

The C programming language was developed in 1972 by Dennis Ritchie at Bell Labs. It was designed as an imperative procedural language that efficiently maps machine instructions to human-readable code: _imperative_ meaning that it consists of statements that determine the behaviour of a progam, and _procedural_ meaning that these statements are executed in sequential order. Due to its efficiency, portability, and low-level capabilities, C remains the dominant language for embedded systems programming decades after its creation.

For embedded systems programmers, C offers several key advantages:

1. Direct hardware access through pointers and memory-mapped I/O
2. Minimal runtime overhead compared to higher-level languages
3. Predictable performance characteristics
4. Fine-grained control over system resources
5. Portability across different microcontroller architectures

Unlike high-level languages that abstract away hardware details, C allows engineers to work closely with the hardware while still maintaining readability and structure. This balance makes it particularly well-suited for STM32 microcontrollers and similar embedded platforms.

## Core C Language Elements

## 1. Data Elements (The "What")

### Variables and Data Types

The foundation of any C program involves variables and their data types. In embedded systems, choosing appropriate data types is crucial for efficient memory usage and performance.

#### Data Type Categories

Data types in C can be categorized into three primary groups:

1. **Primitive (Built-in) Types**: These are the fundamental building blocks provided by the language, including `char`, `int`, `float`, `double`, and `void`.
2. **Derived Types**: These are built upon primitive types and include **Arrays**, **Pointers**, and **Functions**.
3. **User-defined Types**: These allow programmers to create custom data structures tailored to their application, including `struct`, `union`, `enum`, and types created with `typedef`.

#### Primitive Data Types

{: .note }
| Integer Type | Size | Description |
|-------------|------|-------------|
| `char`      | 1 byte | Smallest addressable unit |
| `short`     | 2 bytes | Short integer |
| `int`       | typically 4 bytes | Standard integer |
| `long`      | 4 or 8 bytes | Long integer |
| `long long` | 8 bytes | Extra-long integer |

All integer types can be signed (default) or unsigned.

{: .note }
| Floating-point Type | Size | Description |
|-------------------|------|-------------|
| `float`           | 4 bytes | Single-precision floating point |
| `double`          | 8 bytes | Double-precision floating point |

In embedded systems, floating-point operations may be expensive without hardware floating point unit (FPU) support.

#### Character Type — `char`

The `char` type is fundamentally the smallest integer type in C. While it is primarily used for text, you can perform arithmetic on it just like an `int`. On most microcontrollers like the STM32, a `char` occupies **1 byte** (8 bits), whereas a standard `int` occupies **4 bytes** (32 bits).

- **`char`**: Best for text, ASCII characters, or very small numeric values that stay within the range of an 8-bit integer.
- **`int`**: The native word size for 32-bit microcontrollers, making it the most efficient type for general-purpose calculations.

The `char` type stores numerical values that correspond to characters defined by the **ASCII** (American Standard Code for Information Interchange) standard (e.g., `'A'` is stored as the integer 65).

Characters are represented as literals enclosed in single quotes, such as `'A'`, `'z'`, or `'0'`. C also uses **escape sequences** for special non-printable characters:
- `'\n'` — New line (moves the cursor to the next line)
- `'\r'` — Carriage return (moves the cursor to the start of the current line)
- `'\0'` — Null terminator (essential for marking the end of a string in memory)

---

In embedded C programming, it's best practice to use fixed-width integer types from `<stdint.h>` to ensure consistent behavior across different platforms. These take the form below:

```c
#include <stdint.h>

uint8_t  one_byte;  // Unsigned 8-bit integer
int16_t  two_bytes; // Signed 16-bit integer
uint32_t four_bytes; // Unsigned 32-bit integer
```

Here, the numerical part determines the number of bits in the type and the "u" prefix, or lack of it, determines whether the type is able to store only positive integers, or positive and negative integers, respectively.


#### Variable Declaration, Assignment, and Initialization

Working with variables in C involves three key concepts: declaration, assignment, and initialization.

**Declaration** creates a variable by specifying its data type and name. This reserves memory space for the variable but doesn't set its value:

```c
int counter;         // Declares an integer variable named 'counter'
float temperature;   // Declares a floating-point variable named 'temperature'
char status;         // Declares a character variable named 'status'
```

After declaration, the variable exists but contains an indeterminate value (whatever happened to be in that memory location previously). Using a variable before assigning it a value is a common source of bugs and should be avoided.

**Assignment** sets a value to a previously declared variable using the assignment operator (`=`):

```c
counter = 0;         // Assigns the value 0 to counter
temperature = 25.5;  // Assigns the value 25.5 to temperature
status = 'A';        // Assigns the character 'A' to status
```

**Initialization** combines declaration and assignment in a single statement:

```c
int counter = 0;         // Declares counter and initializes it to 0
float temperature = 25.5; // Declares temperature and initializes it to 25.5
char status = 'A';       // Declares status and initializes it to 'A'
```

Initialization is generally preferred over separate declaration and assignment as it:
1. Makes code more concise
2. Prevents accidentally using uninitialized variables
3. May be more efficient in some cases

When declaring multiple variables of the same type, you can use a single declaration statement:

```c
uint8_t hour = 0, minute = 0, second = 0;  // Multiple initialization
uint16_t adc_values[4];                    // Array declaration
uint32_t *reg_ptr;                         // Pointer declaration
```

#### Variable Scope

Scope defines where a variable can be seen and used within your program.

1. **Global Variables**: These are declared outside all functions (usually at the top of the file). They are accessible by any function in the program and remain in memory for the entire time the program is running.
2. **Local Variables**: These are declared inside a function or a block of code (enclosed in `{}`). They are only accessible within that specific function or block and are destroyed once the function or block finishes executing.

{: .note }
In embedded systems, you should keep global variables to a minimum. They consume RAM permanently and make the code harder to debug because any part of the program can modify them, leading to unexpected "side effects."

#### Integer Ranges and Limits

Understanding the numerical limits of each type is essential for preventing overflow bugs. The range of values an integer type can store depends on the number of bits ($n$) allocated to it:

- **Unsigned Integers**: Can store values from **$0$ to $2^n - 1$**. For example:
  - 8-bit (`uint8_t`): $0$ to $255$
  - 16-bit (`uint16_t`): $0$ to $65,535$
  - 32-bit (`uint32_t`): $0$ to $\approx 4.29 \times 10^9$
- **Signed Integers**: Typically use two's complement representation, allowing values from **$-2^{n-1}$ to $2^{n-1} - 1$**. For example:
  - 8-bit (`int8_t`): $-128$ to $127$
  - 16-bit (`int16_t`): $-32,768$ to $32,767$
  - 32-bit (`int32_t`): $\approx \pm 2.14 \times 10^9$

In embedded systems, engineers must select the smallest data type that safely encompasses the expected range of data to conserve RAM and reduce the number of CPU cycles required for processing.




### Arrays

An array is a collection of elements of the same data type stored in contiguous memory locations. Arrays are essential for handling buffers, sensor data streams, and lookup tables.

```c
uint16_t adc_readings[8];     // Array of 8 unsigned 16-bit integers
float temperatures[4] = {23.5, 24.1, 23.9, 25.0}; // Initialized array
```

Key characteristics of arrays in C:
1. **Zero-indexing**: The first element is always at index `0`.
2. **Contiguous Memory**: Elements are placed directly next to each other in RAM, making arrays ideal for Direct Memory Access (DMA) transfers.
3. **Fixed Size**: The size of an array must be known at compile time.

{: .warning }
C does not perform any array bounds checking. Accessing an index outside the declared size (e.g., `adc_readings[10]`) will access memory that belongs to other variables, leading to hard-to-debug crashes or corrupted data.

To access or modify an element, use the square bracket operator:

```c
adc_readings[0] = 4095; // Write to first element
uint16_t current_val = adc_readings[1]; // Read second element
```

### Structures and Custom Data Types

Structures group related data of different types into a single unit. They are invaluable for organizing complex data in embedded systems:

```c
struct SensorData 
{
    uint32_t id;         // ID — 4 bytes
    float value;        // Data — 4 bytes
    uint16_t threshold; // Limit — 2 bytes
    char status;        // Flag — 1 byte
};
```

To use a structure defined this way, you must use the `struct` keyword with the type name:

```c
struct SensorData reading;
reading.id = 1;
reading.value = 25.5;
reading.threshold = 100;
reading.status = 'A';
```

The `typedef` keyword creates an alias (a new name) for an existing data type. It's often used to make code safer, more readable, and easier to modify. It does **not** create a new data type; it just gives an alternative name.

#### `typedef` for Any Type

You can use `typedef` with any existing type, including primitives and pointers:

```c
typedef unsigned char byte_t;    // descriptive alias for 8-bit data
byte_t mask = 0xAA;

typedef uint32_t handle_t;      // Meaningful name for an internal ID
handle_t sensor_handle = 101;
```

{: .note }
The fixed-width types you've been using (`uint8_t`, `int32_t`, etc.) are themselves `typedef` aliases of standard C types (like `unsigned char` and `signed long`) predefined in `<stdint.h>`.

#### `typedef` with Structures

Use `typedef` to create a shorter name for a structure to avoid typing the `struct` keyword every time you declare a variable. This makes the code much cleaner:

```c
typedef struct 
{
    uint32_t id;
    float value;
    uint16_t threshold;
    char status;
} sensor_data_t;

// Usage: No 'struct' keyword required!
sensor_data_t reading1;
reading1.id = 1;
reading1.value = 25.5;
```

#### Memory Addresses and Pointers

In C, every variable lives at a specific **Memory Address**. A **pointer** is a variable that stores that address—it "points" to where data is stored. While you won't need advanced pointer manipulation for this class, you must understand them because **hardware registers in the STM32 are defined as pointers**.

The memory model below illustrates the concept. The pointer variable itself is stored in memory and its *value* is an address—the address of another variable:

```
Memory:
  Address  │ Value
  ─────────┼───────
  0x2000   │  10      ← uint32_t val = 10;
  0x2004   │  0x2000  ← uint32_t *ptr = &val;  (stores the address of val)
```

**Why this matters for STM32:** Hardware registers like GPIO ports live at fixed addresses decided by the chip manufacturer. The HAL library gives you *pointers* to those addresses so your code can control hardware directly.

##### Pointer Syntax — Anatomy

Reading a pointer declaration is easier when you break it into two parts:

```c
uint32_t * ptr;
│          │
│          └─ Name of the pointer variable
└─ Type of data it points to (a uint32_t lives at that address)
```

| Statement | Meaning |
|---|---|
| `uint32_t val = 10;` | A 32-bit variable holding the value `10` |
| `uint32_t *ptr = &val;` | A pointer variable holding the address of `val` |
| `*ptr` | The value *at* that address (i.e. `10`) |

The `*` symbol has two distinct meanings depending on where it appears:
- In a **declaration** (`uint32_t *ptr`), it means "this is a pointer variable."
- In an **expression** (`*ptr`), it means "go to this address and read the value."

##### Referencing and Dereferencing

Two operators work together to use pointers:

| Operator | Name | Meaning |
|---|---|---|
| `&` | Reference / address-of | "Give me the address of this variable" |
| `*` | Dereference | "Give me the value at this address" |

```c
uint32_t val = 10;
uint32_t *ptr = &val;   // ptr holds the address of val
uint32_t res = *ptr;    // Dereference: follow the address, read value → res = 10

*ptr = 99;              // Write through the pointer: val is now 99
```

Dereferencing a pointer is like following a hyperlink — you go to the location it points to, and you can both read from and write to that location.

#### Pointers to Structures

Pointers can also point to **complex blocks of data** like structures. This is a very powerful concept in embedded systems because it allows us to "remote control" an entire peripheral (like a GPIO port) from a single memory address.

```c
sensor_data_t my_sensor;          // A struct in memory
sensor_data_t *ptr = &my_sensor;  // Pointer to the start of that object
```

To access a member through a pointer, you must **dereference first, then access the member**. The long form uses `*` with parentheses, then the dot operator:

```c
// Long form — dereference, then use the dot operator:
(*ptr).id = 1;

// These two lines do the same thing:
my_sensor.id = 1;
(*ptr).id    = 1;
```

#### The Arrow Operator (`->`)

The parentheses in `(*ptr).member` are easy to get wrong. C provides a cleaner shorthand — the **arrow operator** — that performs both steps at once:

```
ptr->member   ≡   (*ptr).member
```

```c
sensor_data_t my_sensor;
sensor_data_t *ptr = &my_sensor;

my_sensor.id = 1;   // Direct access    (you have the object)
ptr->id      = 1;   // Arrow access     (you have a pointer to the object)
```

The choice of syntax depends on what you have:

| Syntax | When to use |
|---|---|
| `object.member` | You have the object itself |
| `pointer->member` | You have a *pointer* to the object |

You will use the arrow operator for almost all of your hardware interactions on the STM32.

#### Connecting to STM32 — Hardware Registers

All of the above leads directly to how STM32 peripherals are accessed in C. There is nothing magic about it — it is just pointers and structs.

**Step 1 — Registers are grouped into structs** (one struct per peripheral, defined in `stm32f4xx.h`):

```c
typedef struct {
    volatile uint32_t MODER;   // Pin mode register
    volatile uint32_t ODR;     // Output data register
    // ... (other registers)
} GPIO_TypeDef;
```

**Step 2 — A pointer is placed at the fixed hardware address** (also in the device header):

```c
#define GPIOA  ((GPIO_TypeDef *) 0x40020000UL)
```

This casts the known hardware address `0x40020000` to a pointer of type `GPIO_TypeDef *`. `GPIOA` is therefore just a pointer — nothing more.

**Step 3 — You access registers with `->` as normal:**

```c
GPIOA->ODR = 0xFF;    // Write 0xFF to GPIOA's Output Data Register
```

This dereferences `GPIOA` (goes to address `0x40020000`) and accesses the `ODR` member of the struct at that location, which corresponds directly to the physical output data register of GPIO Port A on the chip.

### Bit-fields

Bit-fields allow precise control over the bit width of structure members, which is especially useful for matching hardware register layouts:

```c
typedef struct 
{
    uint32_t enable     : 1;   // 1 bit
    uint32_t direction  : 1;   // 1 bit
    uint32_t mode       : 2;   // 2 bits
    uint32_t prescaler  : 4;   // 4 bits
    uint32_t reserved   : 24;  // 24 bits
} timer_control_t;

timer_control_t timer1;
timer1.enable = 1;      // Enable the timer
timer1.prescaler = 8;   // Set prescaler to 8
```

#### Type Qualifiers

Type qualifiers modify how variables are accessed or used in a program. They provide additional information to the compiler about the variable's intended use, which can help prevent bugs and optimize code. In embedded systems, type qualifiers are particularly important for hardware interaction and resource optimization.

The main type qualifiers in C are:

##### `const`

The `const` qualifier declares that a variable's value cannot be changed after initialization:

```c
const uint16_t MAX_ADC_VALUE = 4095;  // Value cannot be modified
const float PI = 3.14159;            // Mathematical constant
```

Using `const` provides several benefits:
1. Documents that a value should not change
2. Allows the compiler to place data in read-only memory
3. Enables compiler optimizations
4. Prevents accidental modifications


##### `static`

The `static` qualifier serves different purposes depending on where it's used in the code:

1. **File scope (global) variables**: Limits the variable's visibility to the file where it's defined
2. **Function scope (local) variables**: Preserves the variable's value between function calls
3. **Functions**: Limits the function's visibility to the file where it's defined

**Static local variables** retain their value between function calls, which is useful for:
- Maintaining state without global variables
- Implementing counters or accumulators
- One-time initialization

```c
void count_events(void) 
{
    static uint32_t event_counter = 0;  // Initialized only once
    
    event_counter++;
    printf("Event count: %lu\n", event_counter);
}
```

Each time `count_events()` is called, `event_counter` will increment from its previous value rather than starting from 0.

#### **Why not just use a Global?**

Using a `static local` variable is significantly better than using a global variable for this purpose because:

1. **Encapsulation**: No other part of your program can "see" or modify `event_counter`. If you used a global, any other function could accidentally change its value, leading to bugs that are extremely hard to track down.
2. **Namespace Safety**: You can use the name `event_counter` inside multiple functions without any naming conflicts.
3. **Internal Logic**: It clearly communicates to other programmers that this variable *only* exists to support the internal logic of this specific function.

**Static global variables** and functions are only visible within the file where they're defined. This creates a form of encapsulation, preventing external access:

```c
// In timer.c
static uint32_t timer_ticks;       // Only accessible within timer.c
static void update_timer(void);    // Only callable within timer.c

void timer_init(void)              // Globally accessible
{            
    timer_ticks = 0;
    // Setup code
}
```

Using `static` for file-scope variables and functions provides several benefits:
1. Prevents name conflicts across multiple source files
2. Hides implementation details from other modules
3. Enforces proper access through public API functions
4. Improves code organization and modularity

In embedded systems, static variables should be used judiciously as they occupy RAM for the entire program execution.

##### `volatile`

The `volatile` qualifier tells the compiler that a variable's value might change at any time without direct action by the code:

```c
volatile uint8_t interrupt_flag;                           
```

This is critical in embedded systems for any points in code where the value of the variable may change unexpectedly. Some examples include:
1. Memory-mapped hardware registers
2. Variables shared between main code and interrupt service routines
3. Memory locations modified by DMA operations

Without `volatile`, the compiler might optimize away seemingly redundant reads or writes, which could cause unpredictable behavior when interacting with hardware or concurrent code:

```c
// Example: Waiting for a flag set in an Interrupt (ISR)
while (data_ready == 0) 
{
    // Without volatile, the compiler might "optimize" this 
    // by assuming data_ready never changes!
}
```

---

## 2. Operators & Logic (The "How")

### Operators

Operators in C allow you to perform various operations on variables and values. They are essential for implementing logic in embedded systems. C provides several categories of operators:

#### Arithmetic Operators

Arithmetic operators perform mathematical operations on numeric values:

{: .note }
| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `a + b` |
| `-` | Subtraction | `a - b` |
| `*` | Multiplication | `a * b` |
| `/` | Division | `a / b` |
| `%` | Modulo (remainder) | `a % b` |
| `++` | Increment | `a++` or `++a` |
| `--` | Decrement | `a--` or `--a` |

The increment and decrement operators have two forms:
- Prefix (`++a`): Increments the value before it's used in an expression
- Postfix (`a++`): Increments the value after it's used in an expression

```c
uint8_t a = 5;
uint8_t b = ++a;  // b = 6, a = 6
uint8_t c = a++;  // c = 6, a = 7
```

In embedded systems, be cautious with division and modulo operations, as they may be computationally expensive on some microcontrollers without hardware division support.

#### Assignment Operators

Assignment operators assign values to variables, often combining assignment with another operation:

{: .note }
| Operator | Description | Example | Equivalent to |
|----------|-------------|---------|--------------|
| `=` | Simple assignment | `a = b` | |
| `+=` | Add and assign | `a += b` | `a = a + b` |
| `-=` | Subtract and assign | `a -= b` | `a = a - b` |
| `*=` | Multiply and assign | `a *= b` | `a = a * b` |
| `/=` | Divide and assign | `a /= b` | `a = a / b` |
| `%=` | Modulo and assign | `a %= b` | `a = a % b` |
| `<<=` | Left shift and assign | `a <<= b` | `a = a << b` |
| `>>=` | Right shift and assign | `a >>= b` | `a = a >> b` |
| `&=` | Bitwise AND and assign | `a &= b` | `a = a & b` |
| `|=` | Bitwise OR and assign | `a |= b` | `a = a | b` |
| `^=` | Bitwise XOR and assign | `a ^= b` | `a = a ^ b` |

#### Comparison Operators

Comparison operators compare two values and return a boolean result (0 for false, non-zero for true):

{: .note }
| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal to | `a == b` |
| `!=` | Not equal to | `a != b` |
| `>` | Greater than | `a > b` |
| `<` | Less than | `a < b` |
| `>=` | Greater than or equal to | `a >= b` |
| `<=` | Less than or equal to | `a <= b` |

These operators are commonly used in conditional statements and loops:

```c
if (temperature > THRESHOLD) 
{
    activate_cooling();
}
```

#### Logical Operators

Logical operators perform boolean logic operations:

{: .note }
| Operator | Description | Example |
|----------|-------------|---------|
| `&&` | Logical AND | `a && b` |
| `\|\|` | Logical OR | `a \|\| b` |
| `!` | Logical NOT | `!a` |

These operators implement boolean logic and are used primarily in conditional expressions:

```c
if ((temperature > TEMP_MIN) && (temperature < TEMP_MAX)) 
{
    system_state = NORMAL;
}
```

C uses short-circuit evaluation for logical operators. In an AND operation, if the first operand is false, the second is not evaluated. In an OR operation, if the first operand is true, the second is not evaluated.

**Practical Examples:**
```c
// Combined conditions: Both must be true
if (temp > 40 && alarm_enabled) 
{
    activate_fan();
}

// Either condition: True if at least one is met
if (button_pressed || timer_finished) 
{
    wake_system();
}

// Logical NOT: Often used for status flags
if (!system_busy) 
{
    start_processor();
}
```

#### Bitwise Operators

Bitwise operators perform operations on individual bits and are heavily used in embedded systems for efficient register manipulation:

#### Bitwise OR (`|`) — Combining Bits

Used to **combine** bit patterns or **set** bits:

```c
uint8_t temp1 = 0b00000010; // (2)
uint8_t temp2 = 0b01001010; // (74)

uint8_t result = temp1 | temp2;
// result = 0b01001010 (= 0x4A = 74)
```

#### Bitwise AND (`&`) — Masking Bits

Used to **extract** bits or **clear** bits:

```c
uint8_t temp1 = 0b11111101; // (253)
uint8_t temp2 = 0b01001011; // (75)

uint8_t result = temp1 & temp2;
// result = 0b01001001 (= 0x49 = 73)
```

#### Bitwise XOR (`^`) — Toggling Bits

Used to **toggle** (flip) bits:

```c
uint8_t temp1 = 0b00000010; // (2)
uint8_t temp2 = 0b01001010; // (74)

uint8_t result = temp1 ^ temp2;
// result = 0b01001000 (= 0x48 = 72)
```

#### Bitwise Shift (`<<` and `>>`)

Used to move bits left or right:

```c
uint8_t a = 0b00000101; // (5)

uint8_t result_left = a << 2;  // Shift left 2
// result = 0b00010100 (= 20)

uint8_t result_right = a >> 1; // Shift right 1
// result = 0b00000010 (= 2)
```

Common use cases in embedded systems include:

**Basic Patterns:**

1. Setting specific bits in a register:
```c
GPIOA->ODR |= (1 << 5);  // Set bit 5 (turn on LED on pin 5)
```

2. Clearing specific bits:
```c
GPIOA->ODR &= ~(1 << 5);  // Clear bit 5 (turn off LED on pin 5)
```

**Advanced Masking Examples:**

3. Extracting specific bits (Masking):
```c
// Example: Extract bits 0-7 from a 32-bit register
uint8_t low_byte = status_reg & 0xFF; // AND with 0xFF (0b11111111)
```

4. Clearing multiple bits at once:
```c
// Example: Clearing bits 0-3 (the low nibble) at once
GPIOA->ODR &= ~(0xF << 0); // 0xF is 0b1111
```

5. Checking for multiple flags:
```c
if ((status_reg & (FLAG_A | FLAG_B)) == (FLAG_A | FLAG_B)) 
{
    // This executes ONLY if BOTH FLAG_A and FLAG_B are 1
}
```

#### Miscellaneous Operators

C includes a few other operators that are useful in various contexts:

{: .note }
| Operator | Description | Example |
|----------|-------------|---------|
| `sizeof` | Size of variable or type | `sizeof(int)` |
| `&` | Address-of | `&variable` |
| `*` | Dereference pointer | `*pointer` |
| `.` | Structure member | `struct.member` |
| `->` | Structure pointer member | `ptr->member` |
| `?:` | Ternary conditional | `condition ? value1 : value2` |

The ternary operator provides a compact way to express simple conditional assignments:

```c
// Set duty_cycle to MAX_DUTY if temperature > THRESHOLD, otherwise to MIN_DUTY
uint8_t duty_cycle = (temperature > THRESHOLD) ? MAX_DUTY : MIN_DUTY;
```

#### Operator Precedence

C operators follow a precedence order that determines which operations are performed first in an expression. When in doubt, use parentheses to make the order of operations explicit:

```c
// Without parentheses - bitwise AND happens before logical AND
if (flags & MASK_BIT && counter > 0) { ... }

// With parentheses - intention is clear
if ((flags & MASK_BIT) && (counter > 0)) { ... }
```

---

## 3. Grouped Statements (The "Logic")

### Control Structures

Control structures direct the flow of program execution and are essential for implementing embedded system logic.

#### Conditional Statements

The `if`, `else if`, and `switch` statements allow the program to make decisions based on conditions:

```c
if (ADC_value > THRESHOLD) 
{
    LED_ON();
} 
else 
{
    LED_OFF();
}
```

For evaluating multiple conditions, the `switch` statement often provides cleaner code:

```c
switch (system_state) 
{
    case IDLE:
        enter_low_power_mode();
        break;
    case ACTIVE:
        process_sensor_data();
        break;
    case ERROR:
        trigger_alarm();
        break;
    default:
        reset_system();
}
```

#### Loops

Loops are used for repeating sections of code either a fixed number of times or until a condition is met:

The `for` loop is typically used when the number of iterations is known:

```c
for (int i = 0; i < 10; i++) 
{
    send_data_packet(i);
}
```

The `while` loop continues execution as long as its condition remains true:

```c
while (UART_is_receiving()) 
{
    process_byte(UART_read_byte());
}
```

The `do-while` loop ensures the loop body executes at least once:

```c
do 
{
    read_sensor_value();
    process_value();
} 
while (more_readings_available());
```

In embedded systems, infinite loops are common in the main function, with the actual processing occurring in interrupt service routines:

```c
int main(void) 
{
    system_init();
    
    while (1) 
    {
        // This may be empty or contain non-time-critical tasks
        if (flag_set) 
        {
            process_data();
            flag_set = 0;
        }
    }
}
```

## Functions and Program Structure

Functions are blocks of code that perform specific tasks. They enhance code readability, promote reusability, and facilitate modular design—all critical for complex embedded systems.

A well-structured C function includes:

```c
return_type function_name(parameter_type parameter_name, ...) 
{
    // Function body
    return value; // If not void
}
```

A C function consists of several key elements:

1. **Return Type**: Specifies what kind of data the function returns.
   - Can be any valid data type (int, float, char, etc.)
   - `void` if the function doesn't return anything

2. **Function Name**: An identifier that follows C naming conventions.
   - Usually descriptive of the function's purpose
   - Often uses verb-noun format (e.g., `initialize_hardware`, `process_data`)

3. **Parameters**: Input values passed to the function.
   - Each parameter needs both type and name
   - Multiple parameters are separated by commas
   - `void` indicates no parameters

4. **Function Body**: Code enclosed in curly braces that executes when called.
   - Contains declarations, statements, and expressions
   - Can include local variables with scope limited to the function

5. **Return Statement**: Sends a value back to the caller.
   - Must match the declared return type
   - Optional for `void` functions


Example of a complete function:
```c
uint16_t calculate_average(uint16_t *data_array, uint8_t length)
{
    uint32_t sum = 0;           // Local variable
    
    for(uint8_t i = 0; i < length; i++) 
    {
        sum += data_array[i];   // Function logic
    }
    
    return (uint16_t)(sum / length);  // Return statement
}
```


### Function Prototypes

Function prototypes declare a function before its implementation, allowing the compiler to perform type checking:

```c
// Prototype - BEFORE main()
void initialize_hardware(void);

int main(void) 
{
    initialize_hardware(); // Compiler knows the function exists
    // Rest of program
}

// Implementation - AFTER main()
void initialize_hardware(void) 
{
    // Initialization code
}
```

---

## 4. Structural & System Elements (The "System")

### Pointers and Memory Management

Pointers are variables that store memory addresses. They are essential in embedded programming for:

1. Manipulating hardware registers directly
2. Efficient data handling without copying large structures
3. Dynamic memory allocation (though this is often avoided in embedded systems)
4. Callback mechanisms and function pointers

A pointer is declared using the asterisk (`*`) symbol:

```c
uint32_t *ptr;  // Pointer to an unsigned 32-bit integer
```

To access the value a pointer references (dereferencing), use the asterisk operator:

```c
uint32_t value = *ptr;  // Read the value at the address stored in ptr
*ptr = 0x1000;         // Write to the address stored in ptr
```

To get the address of a variable, use the address-of operator (`&`):

```c
uint32_t variable = 42;
ptr = &variable;       // ptr now points to variable
```

When working with structures through pointers, the arrow operator (`->`) provides a convenient shorthand:

```c
accelerometer_data_t *reading_ptr = &reading;
reading_ptr->x = 150;  // Equivalent to (*reading_ptr).x = 150;
```

### Pointers and Hardware Registers

In embedded systems, hardware peripherals are controlled through special memory-mapped registers. Pointers provide direct access to these registers:

```c
// Define a pointer to the GPIO output data register
volatile uint32_t *GPIO_ODR = (uint32_t *)0x40020014;

// Set bit 5 (turn on an LED connected to pin 5)
*GPIO_ODR |= (1 << 5);
```

The `volatile` keyword is crucial when working with hardware registers, as it prevents the compiler from optimizing away seemingly redundant reads or writes.

### Header Files

Well-organized embedded C projects separate interfaces from implementations using header files:

- Header files (`*.h`) contain declarations, prototypes, and preprocessor directives
- Source files (`*.c`) contain function implementations

A typical header file structure includes:

```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

// Includes
#include <stdint.h>

// Type definitions
typedef struct 
{
    uint8_t id;
    uint16_t value;
} sensor_data_t;

// Function prototypes
void sensor_init(void);
sensor_data_t sensor_read(void);

#endif /* MODULE_NAME_H */
```

This structure prevents multiple inclusion of the same header (using include guards) and clearly defines the module's interface.

### Main Program Structure

In embedded systems, the structure of the `main.c` file follows a pattern that reflects the lifecycle of the embedded application. A typical embedded C program has the following structure:

```c
// Includes  ------------------------------------------------------------------

#include <stdio.h> 
#include <math.h>

// Global variables  ----------------------------------------------------------

float a = 67;

// Function declarations  -----------------------------------------------------

void main();

// Main function  -------------------------------------------------------------

void main()
{
    printf("sqrt(67)=%f", sqrt(a)); //This line calculates and displays the 
                                    //sqare root of "a" using the sqrt function
    return 0;
}

// Function implementations ---------------------------------------------------


// END  -----------------------------------------------------------------------

```

### Memory-Mapped I/O

STM32 microcontrollers use memory-mapped I/O, where peripheral registers appear as memory locations. This approach simplifies hardware control:

```c
// Define base addresses for peripherals
#define GPIOA_BASE      0x40020000     //0x40020000 is the memory location of the first GPIOA register
#define GPIOB_BASE      0x40020400

// Define register offsets
#define GPIO_MODER_OFFSET   0x00       //The moder register is located 0 positions away forom the base register
#define GPIO_ODR_OFFSET     0x14       //The ODR register is located 0x14 positions away forom the base register

// Define pointers to specific registers
volatile uint32_t *GPIOA_MODER = (uint32_t *)(GPIOA_BASE + GPIO_MODER_OFFSET);
volatile uint32_t *GPIOA_ODR = (uint32_t *)(GPIOA_BASE + GPIO_ODR_OFFSET);

```

## Preprocessor Directives

The preprocessor processes C code before compilation, handling tasks like file inclusion, macro expansion, and conditional compilation. These features are particularly useful in embedded systems for configuration and portability.

### Include Directives

The `#include` directive incorporates the contents of another file:

```c
#include <stdint.h>      // System header (angle brackets)
#include "uart_driver.h" // Project header (quotes)
```

System headers (with angle brackets) are searched in the compiler's include path, while project headers (with quotes) are first searched in the current directory.

### Macro Definitions

Macros define constants or simple functions that are expanded by the preprocessor:

```c
#define LED_PIN     5
#define SET_BIT(REG, BIT) ((REG) |= (1 << (BIT)))

// Usage
SET_BIT(GPIOA->ODR, LED_PIN);
```

Macros can make code more readable and maintain consistency, but they lack type checking and can lead to unexpected behavior if not carefully designed.

### Conditional Compilation

Conditional compilation directives allow different code sections to be included based on defined conditions:

```c
#define DEBUG_LEVEL 2

#if DEBUG_LEVEL > 1
    #define DEBUG_PRINT(msg) uart_send_string(msg)
#elif
    #define DEBUG_PRINT(msg) /* nothing */
#endif
```

This feature is valuable for creating configurable code that can adapt to different hardware platforms or debugging needs without runtime overhead.

## Conclusion

C programming for embedded systems combines the power of a systems programming language with the constraints of resource-limited environments. By understanding the language features and applying best practices, you can develop efficient, reliable, and maintainable embedded software for STM32 microcontrollers and similar platforms.

As you continue in your embedded systems journey, these foundational C programming concepts will serve as building blocks for more advanced topics like communication protocols, real-time operating systems, and complex peripheral control. 