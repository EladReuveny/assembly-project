  <h1>Assembly to Machine Code Converter</h1>

  <h2>📜 Description</h2>
  <p>This project is an <strong>Assembly to Machine Code Converter</strong> written in <strong>C</strong>. It processes assembly language files, translating them into machine code. The converter handles macros, analyzes instructions, manages symbols, and generates the corresponding machine code output.</p>

  <h2>🧠 Features</h2>
  <ul>
    <li><strong>Macro Processing:</strong> Expands macros within assembly files.</li>
    <li><strong>Instruction Analysis:</strong> Parses and interprets assembly instructions.</li>
    <li><strong>Symbol Management:</strong> Handles symbols and their addresses.</li>
    <li><strong>Machine Code Generation:</strong> Produces machine code output files from assembly source files.</li>
  </ul>

  <h2>📁 Project Structure</h2>
  <pre>
assembly-project/
├── .gitignore  <!-- Git ignore file -->
├── CMakeLists.txt  <!-- CMake build configuration -->
├── makefile  <!-- Build script for compiling the project -->
├── assembler  <!-- Executable output after compilation -->
├── assembler.c  <!-- Main program handling the assembly process -->
├── assembler.o  <!-- Object file for assembler -->
├── analyze.c  <!-- Analyzes assembly instructions -->
├── analyze.h  <!-- Header file for analyze.c -->
├── analyze.o  <!-- Object file for analyze -->
├── instructions.c  <!-- Defines supported instructions and their properties -->
├── instructions.h  <!-- Header file for instructions.c -->
├── instructions.o  <!-- Object file for instructions -->
├── machinecode.c  <!-- Generates machine code from parsed instructions -->
├── machinecode.h  <!-- Header file for machinecode.c -->
├── machinecode.o  <!-- Object file for machinecode -->
├── macro.c  <!-- Processes macros in assembly files -->
├── macro.h  <!-- Header file for macro.c -->
├── macro.o  <!-- Object file for macro -->
├── symbols.c  <!-- Manages symbol table and addresses -->
├── symbols.h  <!-- Header file for symbols.c -->
├── symbols.o  <!-- Object file for symbols -->
├── utilities.c  <!-- Utility functions used across the project -->
├── utilities.h  <!-- Header file for utilities.c -->
├── utilities.o  <!-- Object file for utilities -->
├── data.h  <!-- Shared data structures and definitions -->
├── file1.as  <!-- Example assembly source file -->
├── file1.ent  <!-- Additional file related to assembly (e.g., entry points) -->
├── file1.ext  <!-- External file for linking -->
├── file1.ob  <!-- Corresponding machine code output file -->
├── file2.as  <!-- Another example assembly source file -->
├── file2.ob  <!-- Corresponding machine code output file for file2 -->
├── file3.as  <!-- Another example assembly source file -->
├── file4.as  <!-- Another example assembly source file -->
└── .gitignore  <!-- Git ignore file -->
  </pre>

  <h2>⚙️ Compilation and Execution</h2>

  <h3>Using Makefile</h3>
  <ol>
    <li><strong>Compile the project:</strong>
      <pre><code>make</code></pre>
    </li>
  <li><strong>Run the assembler:</strong>
    <pre><code>./assembler &lt;file_name&gt;</code></pre>
    <p>Example: <code>./assembler file1.as</code></p>
  </li>
    <p>This command processes <code>file1.as</code> and generates the corresponding machine code output.</p>
  </ol>

  <h3>Using CMake</h3>
  <ol>
    <li><strong>Generate build files:</strong>
      <pre><code>cmake .</code></pre>
    </li>
    <li><strong>Build the project:</strong>
      <pre><code>make</code></pre>
    </li>
    <li><strong>Run the assembler:</strong>
      <pre><code>./assembler file1.as</code></pre>
    </li>
  </ol>

<h2>🧪 Example</h2>

<p><strong>Input (<code>file1.as</code>):</strong></p>
<pre><code>
.entry LENGTH
    .extern W
MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
prn -5
bne W
sub @r1, @r4
    bne L3
L1: inc K
    .entry LOOP
jmp W
END: stop
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 22
    .extern L3
</code></pre>

<p><strong>Entry Points (<code>file1.ent</code>):</strong></p>
<pre><code>
LENGTH 125
LOOP 103
</code></pre>

<p><strong>External Symbols (<code>file1.ext</code>):</strong></p>
<pre><code>
W 108
L3 112
W 116
</code></pre>

<p><strong>Output (<code>file1.ob</code>):</strong></p>
<pre><code>
oM
GA
H2
Es
HG
GE
/7
FM
AB
p0
CQ
FM
AB
Ds
IC
Es
AB
Hg
Bh
Bi
Bj
Bk
Bl
Bm
AA
AG
/3
AP
AW
</code></pre>



  <h2>🛠️ Dependencies</h2>
  <ul>
    <li><strong>C Compiler:</strong> GCC or Clang</li>
    <li><strong>Build System:</strong> Make or CMake</li>
  </ul>

  <hr>

  <p><em>For more details, refer to the source code and comments within the repository.</em></p>

