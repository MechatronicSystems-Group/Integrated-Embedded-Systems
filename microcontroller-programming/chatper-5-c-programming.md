---
layout: page
title: "Chapter 5: C Programming for Embedded Systems"
parent: Microcontroller Programming
nav_order: 1
---

# C Programming for Embedded Systems

C programming forms the foundation of embedded systems development. As a systems programming language, C provides an efficient mapping between human-readable code and machine instructions, making it ideal for resource-constrained embedded applications.

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

### Variables and Data Types

The foundation of any C program involves variables and their data types. In embedded systems, choosing appropriate data types is crucial for efficient memory usage and performance.

C provides several primitive data types:

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
// Without volatile, compiler might optimize this to a single read
while (device_status_register & BUSY_FLAG) 
{
    // Wait for device to be ready
}
```

### Structures and Custom Data Types

Structures group related data of different types into a single unit. They are invaluable for organizing complex data in embedded systems:

```c
typedef struct 
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
} accelerometer_data_t;
```

The `typedef` keyword creates an alias for the structure type, simplifying subsequent declarations:

```c
accelerometer_data_t reading;
reading.x = 100;
reading.y = 200;
reading.z = 300;
```

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

#### Bitwise Operators

Bitwise operators perform operations on individual bits and are heavily used in embedded systems for efficient register manipulation:

{: .note }
| Operator | Description | Example |
|----------|-------------|---------|
| `&` | Bitwise AND | `a & b` |
| `\|` | Bitwise OR | `a \| b` |
| `^` | Bitwise XOR | `a ^ b` |
| `~` | Bitwise NOT (complement) | `~a` |
| `<<` | Left shift | `a << b` |
| `>>` | Right shift | `a >> b` |

Common use cases in embedded systems include:

1. Setting specific bits in a register:
```c
GPIOA->ODR |= (1 << 5);  // Set bit 5 (turn on LED on pin 5)
```

2. Clearing specific bits:
```c
GPIOA->ODR &= ~(1 << 5);  // Clear bit 5 (turn off LED on pin 5)
```

3. Toggling bits:
```c
GPIOA->ODR ^= (1 << 5);  // Toggle bit 5 (toggle LED state)
```

4. Checking if a bit is set:
```c
if (GPIOA->IDR & (1 << 0)) 
{
    // Bit 0 is set (button pressed)
}
```

5. Creating bit masks:
```c
#define GPIO_PIN_MASK(x) (1 << (x))
GPIOA->ODR |= GPIO_PIN_MASK(5) | GPIO_PIN_MASK(6);  // Set pins 5 and 6
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

## Pointers and Memory Management

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