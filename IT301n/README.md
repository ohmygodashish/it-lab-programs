### Experiment 1: Implement a NFA to recognize keywords in lexical analysis (utilize a main program and function calls for the NFA; employ a switch/case statement within the NFA)

In compiler design, lexical analysis is the first phase where the source code is scanned to produce tokens. Keywords are reserved words like "if", "else", "while", "for", and "int" that have special meaning in the language. A Non-deterministic Finite Automaton (NFA) is a theoretical model used to recognize patterns in strings, consisting of states, transitions, an initial state, and accepting states. NFAs allow multiple transitions for the same input or epsilon transitions, making them suitable for pattern matching in lexers. In implementation, a switch/case structure simulates state transitions by checking the current state and input character, advancing states for valid sequences. The main program takes input and calls the NFA function to check if it reaches an accepting state, identifying the input as a keyword or rejecting it. This approach is efficient for fixed patterns like keywords, as NFAs can be converted to Deterministic Finite Automata (DFA) for optimization, but direct simulation suffices for small sets.

### Experiment 2: Implement NFAs to recognize variables and numbers in lexical analysis

Variables (identifiers) and numbers (constants) are fundamental tokens in lexical analysis. Identifiers typically start with a letter or underscore followed by alphanumeric characters or underscores (e.g., "ab", "_var1"). Numbers can be integers (e.g., "123") or floats (e.g., "12.34"). NFAs model these with states: for identifiers, start in state 0, transition to state 1 on valid first character, and loop in state 1 for subsequent characters. For numbers, state 0 transitions to state 1 on digits, optionally to state 2 on decimal point, then to state 3 for fractional digits, accepting in states 1 or 3. This separates lexical tokens from the source stream, handling ambiguities like distinguishing keywords from identifiers. In practice, the lexer uses these NFAs in a combined automaton to prioritize longer matches (maximal munch rule) and pass tokens to the syntax analyzer.

### Experiment 3: Implement NFAs to recognize relational operators, arithmetic operators, parenthesis, and white space in lexical analysis

Relational operators (e.g., >, <, >=, <=, ==, !=) compare values, arithmetic operators (e.g., +, -, *, /, %) perform operations, parentheses ((), ) group expressions, and whitespace (spaces, tabs, newlines) separates tokens. NFAs for these are simple: single-state for single-character tokens (e.g., arithmetic, parentheses, whitespace loops), and multi-state for multi-character ones (e.g., relational starts in state 0, transitions to state 1 on =, >, etc., and state 2 on = for compounds). Whitespace NFA loops on valid characters and accepts non-empty sequences but is often ignored in token streams. These NFAs ensure accurate token boundaries, preventing misreads like "++" as two + operators. In lexical analysis, they integrate with other recognizers, using backtracking if needed for ambiguous inputs.

### Experiment 4: Write a program to generate tokens for the high-level source code: while (ab>=a1+b1)

Token generation in lexical analysis breaks source code into meaningful units like keywords, identifiers, operators, and symbols. For "while (ab>=a1+b1)", tokens might include: KEYWORD("while"), LPAREN("("), ID("ab"), RELOP(">="), ID("a1"), ADDOP("+"), ID("b1"), RPAREN(")"). The program scans character-by-character, using finite automata or regular expressions to match patterns, buffering inputs, and outputting token-type pairs. Errors occur on invalid characters. This phase handles comments, whitespace skipping, and symbol table insertion for identifiers, preparing input for syntax analysis. Importance: Efficient tokenization reduces parsing complexity and enables error detection at the lexical level.

### Experiment 5: Write a program to eliminate left recursion from the given grammar

Left recursion in context-free grammars (CFGs) occurs when a non-terminal derives itself as the first symbol (e.g., A → Aα | β), causing infinite loops in top-down parsers like recursive descent or LL. Elimination transforms it to right recursion: Introduce A' → αA' | ε, then A → βA'. The program parses the grammar, identifies left-recursive productions, applies the transformation, and outputs the equivalent non-recursive grammar. This is essential for LL parsing, preserving language equivalence while enabling predictive parsing without backtracking. Direct left recursion is handled first; indirect requires additional steps like substitution.

### Experiment 6: Write a program to perform left factoring on the given grammar

Left factoring resolves non-determinism in grammars where multiple productions start with the same prefix (e.g., A → αβ | αγ), making LL parsers unable to choose without lookahead. Factoring extracts the common α: A → αA', A' → β | γ. The program scans productions, finds common prefixes, introduces new non-terminals, and rewrites the grammar. This ensures the grammar is LL(1) suitable, with unique transitions per input symbol, improving parser efficiency and eliminating choice ambiguities.

### Experiment 7: Write a program to find the FIRST set for the given grammar

The FIRST set of a non-terminal is the set of terminals that can begin strings derived from it, including ε if it derives empty. Computation: For X → a..., FIRST(X) includes a; for X → Y..., union FIRST(Y) (removing ε and recursing); handle ε by propagating to next symbols. The program uses fixed-point iteration over productions, storing sets in maps. FIRST aids LL parsing table construction by predicting productions based on input symbols, detecting conflicts if sets overlap.

### Experiment 8: Write a program to find the FOLLOW set for the given grammar

The FOLLOW set of a non-terminal A is the set of terminals that can appear immediately after A in derivations, including $ (end marker) for the start symbol. Computation: Traverse productions; if B → αAβ, add FIRST(β) to FOLLOW(A); if β derives ε, add FOLLOW(B). Use iteration for propagation. The program builds sets via maps, requiring FIRST sets first. FOLLOW resolves ε-productions in LL tables, adding entries when FIRST includes ε, ensuring complete coverage for parsing.

### Experiment 9: Write a program to construct the LL(1) parsing table for the given grammar

LL(1) parsing is top-down, using a table M[non-terminal, terminal] to select productions based on one lookahead symbol. Construction: For each production A → α, add to M[A, t] where t in FIRST(α); if ε in FIRST(α), add to M[A, f] where f in FOLLOW(A). The grammar must be left-recursion-free, left-factored, and conflict-free (no multiple entries per cell). The program computes FIRST/FOLLOW, then fills a 2D table, flagging errors. This table drives predictive parsing, enabling efficient syntax checking without backtracking.

### Experiment 10: Write a program to parse the string id = id+id generating a sequence-of-moves table based on the LL(1) parsing table

Parsing validates if a string belongs to the language using the LL(1) table. Start with stack containing $ and start symbol, input with string + $. Moves: Match terminals by popping; for non-terminals, push production right-hand side (reversed) based on table entry. The sequence-of-moves table logs stack, input, and action at each step. For "id = id+id", assume grammar like E → id = E, E → E + id | id. The program simulates the stack-based parser, outputting accept/reject. This demonstrates syntax analysis, error recovery, and parse tree implicit construction.

### Experiment 11: Write a program to generate three-address (intermediate) code for the given source code

Intermediate code generation in semantic analysis translates parsed syntax trees to machine-independent forms like three-address code (TAC), where statements are like x = y op z (up to three operands). For expressions, use post-order traversal: temporary variables for subexpressions, operators for assignments/loops. Control structures convert to labels/jumps. The program walks the AST, emitting TAC lines. Benefits: Optimizes code (e.g., common subexpression elimination), facilitates retargeting to different architectures, and bridges front-end (analysis) to back-end (optimization/codegen).

### Experiment 12: Write a program to implement a shift-reduce parser/LR parser

Shift-reduce parsing is bottom-up, using a stack and LR table for actions: shift (push token), reduce (pop handle, push non-terminal), accept, or error. LR(0)/SLR/LR(1)/LALR variants differ in lookahead; SLR uses FOLLOW for reductions. The program builds an item set (closures/gotos), constructs action/goto tables, then parses input by consulting tables. Handles shift-reduce/reduce-reduce conflicts. Superior for broader grammars than LL, as it parses left-to-right with rightmost derivation in reverse, common in tools like Yacc.

### (No Code) Experiment 13: Implement a Lexical Analyzer to tokenize the input using Lex

Lex (or Flex) is a lexical analyzer generator that takes regular expressions and actions, producing a C program with yylex() to scan input. Specifications: patterns for tokens (e.g., [a-z]+ {return ID;}), ignoring whitespace. The generated DFA-based scanner handles longest-match and priority rules. In compiler pipelines, it interfaces with parsers via tokens. Advantages: Automates complex pattern matching, supports symbol tables, and speeds development over manual NFAs.

### (No Code) Experiment 14: Write a program to design LALR parser using Yacc

Yacc (or Bison) generates LALR(1) parsers from CFG rules with actions for semantic processing. Input: %token declarations, rules like expr : expr '+' term {$$ = $1 + $3;}, precedence. It builds LR tables, handling conflicts via associativity. The program uses yyparse() to drive syntax analysis, integrating with Lex for tokens. LALR combines LR(1) power with smaller tables than canonical LR, ideal for programming languages, enabling AST building and error reporting.