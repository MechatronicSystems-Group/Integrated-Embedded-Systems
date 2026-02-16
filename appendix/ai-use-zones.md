---
title: "AI Use Zones for MEC4126F"
parent: Appendices
nav_order: 3
published: false
---

# AI Use Zones for MEC4126F

The use of generative AI tools in education presents both opportunities and challenges. This framework establishes three zones—Green, Yellow, and Red—to help you understand when and how AI can be used responsibly in this course. These zones are designed to support your learning while maintaining academic integrity and ensuring you develop the skills necessary to become a competent engineer.

## The Three Zones

### Green Zone: AI as a Learning Tool

The Green Zone represents appropriate, encouraged use of AI tools to support your learning. In this zone, AI acts as a tutor, debugger, and study aid; not as a replacement for your own thinking.

{:.green-zone}
> **Appropriate uses in the Green Zone:**
> 
> 1. **Concept Explanation**: Asking AI to explain programming concepts, syntax, or error messages you don't understand.
> 2. **Debugging Assistance**: Sharing your own code that isn't working and asking for help identifying the problem.
> 3. **Code Review**: Getting feedback on code you've written to improve style, efficiency, or clarity.
> 4. **Approach Critique**: Asking AI to explain why your approach to a problem may not be working after you've tried it.
> 5. **Documentation Help**: Understanding library functions, register definitions, etc.
> 6. **Study Aid**: Generating practice problems or explaining solutions to past exam questions.

{:.green-zone}
> **Example Green Zone interaction:**
> 
> *Student:* "I'm getting a build error in this code I wrote. I've read the debug trace, but I can't figure out what's wrong. Can you help me understand why?"
> 
> *AI:* [Explains the likely cause and suggests a solution.]
> 
> *Student:* [Uses the explanation to fix their own code and learns from the mistake]

{: .note }
> **Key principle for Green Zone:** You must understand and be able to explain any code or concept you submit. If you cannot explain your solution line-by-line, you have not used AI appropriately. Pracs are marked through demonstration of your solution, where questions may be asked.

### Yellow Zone: AI-Assisted Work with Full Understanding

The Yellow Zone represents situations where AI-generated code may be incorporated into your work, but only under strict conditions that ensure learning still occurs. This zone requires transparency and a demonstrated understanding of the work you submit.

{:.yellow-zone}
> **Conditions for Yellow Zone use:**
> 
> 1. **Full Comprehension**: You must completely understand any AI-generated code you use—you should be able to explain every line, modify it, and debug it independently. The key aim of the course is for you to achieve _learning_ in the course material. If this isn't achieved, the use of the AI tools is not appropriate.
> 2. **Substantial Original Work**: The majority of the codebase should still be your own work; AI assists with specific, well-defined sub-problems.
> 3. **Testing and Verification**: You must thoroughly test AI-generated code and verify it works correctly in your specific context.
> 4. **Documentation**: You must document which parts of your code were AI-assisted and how you verified its correctness.
> 5. **No Core Algorithms**: AI should not be used to generate the primary algorithmic or design logic that the assessment is testing.
  
> **Example Yellow Zone interaction:**
> 
> *Student:* "I've implemented the PID controller myself, but I need a helper function to calculate the moving average of my sensor readings. Can you suggest an efficient implementation?"
> 
> *AI:* [Provides a moving average function]
> 
> *Student:* [Reviews the code, understands how it works, tests it thoroughly, integrates it, and documents the assistance. The student is then prepared to explain the code in person to a tutor or examiner.]

{: .note }
> **Key principle for Yellow Zone:** AI is a tool you use, not a replacement for your expertise. You remain fully responsible for the correctness and quality of the final submission.

### Red Zone: Prohibited Use

The Red Zone represents uses of AI that undermine the learning objectives of the assessment and constitute academic misconduct. Submitting work from the Red Zone will be treated as a violation of academic integrity.

{:.red-zone}
> **Prohibited uses in the Red Zone:**
> 
> 1. **Direct Submission**: Submitting AI-generated code without understanding, modifying, or verifying it.
> 2. **Complete Solutions**: Asking AI to solve an entire assignment problem or write substantial portions of required functionality.
> 3. **Obfuscation**: Using AI to modify code in an attempt to hide that it was AI-generated.
> 4. **Exam and Test Use**: Using AI during any closed-book assessment, including in-person tests and exams.
> 5. **False Attribution**: Claiming AI-generated work as entirely your own without disclosure.
> 6. **Bypassing Learning**: Using AI to complete assignments without engaging with the underlying concepts.

{:.red-zone}
> **Example Red Zone violation:**
> 
> *Student:* "Write me a complete STM32 program that reads an ADC, applies a moving average filter, and outputs the result via UART. Include all the register configurations."
> 
> *AI:* [Generates complete, working code]
> 
> *Student:* [Submits the code without understanding how it works, cannot explain the register configurations during oral assessment]

{:.caution}
> **Key principle for Red Zone:** If AI is doing the thinking, you are not learning. The goal of assessments is to develop your competence, not to produce working code by any means necessary.

## The 2025 Case Study in MEC4126F

The 2025 class saw widespread use of AI tools on programming parts of the practicals. While many students submitted working code, the data revealed a concerning pattern:

- Students achieved similar marks in practicals to previous years despite increased AI usage.
- 14 academic misconduct cases were identified and reported for inappropriate AI use.
- The practical exam performance, where AI use was prohibited, was the lowest in the past 5 years with an average mark of 47% being achieved and a pass rate of 44%.

This pattern suggests that students were often unable to recognise when their use of AI was inappropriate and further, that AI use had replaced learning rather than supported it. 

### The Professional Reality

As a mechatronic engineer, you will be expected to:

- Debug hardware and software issues in the field where they may be without internet access.
- Review and sign off on designs where, "the AI said it was fine" is not a defense.

- Work within safety-critical systems where errors have real consequences.

{: .note }
> The Green and Yellow Zones prepare you for this reality. The Red Zone leaves you unprepared.

## Practical Guidelines for Responsible AI Use

### Before Using AI, Ask Yourself:


1. *Have I attempted this myself first?* AI should help you get unstuck, not prevent you from ever being stuck.

2. *Will I understand the result?* If you cannot explain the AI's output, you should not use it.

3. *What am I actually learning?* If the answer is "nothing" or "how to prompt AI," reconsider your approach.

4. *Could I do this in an exam?* If not, you need more practice without AI assistance.

### Building Your AI Literacy

Responsible AI use is itself a skill. To use AI effectively as an engineer, here are some guidelines that may help build responsible habits:

**Verify everything**: AI can generate plausible-looking nonsense. In embedded systems, that nonsense can damage hardware.

**Understand limitations**: AI has no understanding of your specific hardware, constraints, or context unless you specifically tell it these details.

**Develop critical evaluation**: Learn to spot when AI output is wrong, inefficient, or inappropriate.

**Practice without AI**: Regularly solve problems completely on your own to maintain and build your skills.

### Documentation Requirements

When you use AI in the Yellow Zone, include a brief note in your submission:

```
AI Use Declaration:
- Used AI to generate the moving average filter function (lines 45-62).
- Modified the function to use fixed-point arithmetic for performance.
- Verified correctness against known test cases.
- Fully understand the implementation and can explain it. (Actually prepare for this as you may be asked to do so.)
```

{:.tip}
> This transparency is not penalised—it demonstrates professional integrity and helps us understand how AI is being used in the course.

## Assessment-Specific Policies

Different assessments may have different AI use policies. Always check the specific instructions for each assignment:

| Assessment Type | Typical AI Policy |
|-----------------|-------------------|
| Weekly programming practicals | Green and Yellow Zone permitted |
| Problem sets | Green and Yellow Zone permitted |
| In-lab practical exam | No AI use (simulates professional field conditions) |
| Tests and exams | No AI use (closed-book, closed-internet) |

{:.caution}
> When in doubt, ask. It is always better to clarify before submitting than to face an academic integrity investigation after.

## Summary of AI Use Zones

| Zone | Description | Analogy |
|------|-------------|---------|
| **Green** | AI as tutor and debugger; full understanding required | Using a calculator to check your work |
| **Yellow** | AI-assisted with transparency; you remain responsible | Using CAD software to design a part you fully understand |
| **Red** | AI replaces your thinking; academic misconduct | Submitting someone else's work as your own |


{:.red-zone}
> Choose your zone wisely. Attempt to always stay in the Green!

## UCT Framework for AI in Education 

The UCT Framework for AI in Education can be found here: 

[UCT AI in Education Framework](docs/uct-ai-in-education-framework-june-2025-final.pdf)
