# Question 10-1: Example 10 -4 generates the answer 47 instead of the expected answer 144. Why? (See the hint below.)
<code>
#include  &ltstdio.h&gt <br>
#define FIRST_PART 7 <br> 
#define LAST_PART 5 <br>
#define ALL_PARTS FIRST_PART + LAST_PART <br>
int main() {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("The square of all the parts is %d\n", ALL_PARTS * ALL_PARTS); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code> <br>

## RESPOSTA<br>
<code>
#include  &ltstdio.h&gt <br>
#define FIRST_PART 7 <br> 
#define LAST_PART 5 <br>
#define ALL_PARTS (FIRST_PART + LAST_PART) <br>
int main() {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("The square of all the parts is %d\n", ALL_PARTS * ALL_PARTS); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code> <br>

### EXPLICAÇÃO: O codigo sem os () vai ler em ordem com precedencia, no caso o programa irira ler da seguinte forma 7 + 5 * 7 + 5  => 7 + 35 + 5 o que resultaria em 47, já com o () o código será lido da seguinte maneira (7 + 5) * (7 + 5)  => (12) * (12) que resulta em 144  o que é o esperado <br>
<br>

# Question 10-4: Example 10 -7 is supposed to print the message "Fatal Error: Abort" and exit when it receives bad data. But when it gets good data, it exits. Why?
<code>
#include &ltstdio.h&gt <br>
#include &ltstdlib.h&gt <br>
#define DIE \ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fprintf(stderr, "Fatal Error:Abort\n");exit(8); <br>
int main() { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* a random value for testing */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int value; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;value = 1; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if (value < 0) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DIE; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("We did not die\n"); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code>
,br
## RESPOSTA <br>
<code>
#include &ltstdio.h&gt <br>
#include &ltstdlib.h&gt <br>
#define DIE \ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fprintf(stderr, "Fatal Error:Abort\n");exit(8); <br>
int main() { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* a random value for testing */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int value; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;value = 1; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if (value < 0) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DIE; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("We did not die\n"); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code>

### EPLICAÇÃO: Sem a declaração do escopo do if o programa não irá pegar o printf pois já que não esta declarado onde acaba o if, então o código esta presumindo que printf("We did not die\n"); pertence ao if. Quando colocamos um valor menor que 0 ele não imprime o segundo printf pois no final de DIE tem tem uma chamada de saida(8), então o código acaba logo ali, mesmo tendo mais coisas para fazer dentro do escopo do if. <br>
<br>

# Question 10-5: What does Example 10-8 output? Try running it on your machine. Why did it output what it did? Try checking the output of the preprocessor.
<code>
#include &ltstdio.h&gt <br>
#define SQR(x) (x * x) <br>
int main(){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int counter; /* counter for loop */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for (counter = 0; counter < 5; ++counter) { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("x %d, x squared %d\n",counter+1, SQR(counter+1)); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;} <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}

</code>

## RESPOSTA
<code>
x 1, x squared 1 <br>
x 2, x squared 3 <br>
x 3, x squared 5 <br>
x 4, x squared 7 <br>
x 5, x squared 9 <br>
</code>

### EXPLICAÇÃO: A explicação para esse código se da pela a segunte forma: novamente  é usado a ordem de precedencia, então a operação será da seguinte maneira  counter + 1 * counter + 1, logo sera counter + ( 1 * counter) + 1 e isso acaba resultando na saida acima <br>

<br>
# Question 10-6: Why will Example 10-9 not produce the expected output? By how much will the counter go up each time?

<code>
#include &ltstdio.h&gt <br>
#define SQR(x) ((x) * (x)) <br>
int main(){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int counter; /* counter for loop */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Counter = 0; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;while (counter < 5)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("x %d square %d\n", counter, SQR(++counter)); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code>

## RESPOSTA
<code>
#include &ltstdio.h&gt <br>
#define SQR(x) ((x) * (x)) <br>
int main(){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int counter; /* counter for loop */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Counter = 0; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;while (counter < 5){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("x %d square %d\n", counter, SQR(counter+1)); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;counter++ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code>

### EXPLICAÇÃO: O programa não executa completamente todos os passos do loop pois o counter esta sendo incrementado, para que o loop aconteça de forma correta ( rodando 5 vezes, o que seria esperado), é necessario não incrementar o counter dentro do printf da seguinte forma ++counter e sim  printf("x %d square %d\n", counter, SQR(counter +1)); e logo após fazer o counter++ para que o while tenha uma condição de parada. A cada laço incremetna 2 em counter. Ademais que pode ter sido um erro de digitação, mas caso não seja o programa travaria na linha do Counter  = 0 travaria o programa pois Counter com C maiusculo não esta declarado e sim counter com c minusculo, já que a linguem C é case sensitive. <br>
<br>

# Question 10-7: Example 10-10 tells us that we have an undefined variable number, but our only variable name is counter .
<code>
#include &ltstdio.h&gt <br>
#define RECIPROCAL (number) (1.0 / (number)) <br>
int main() { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float counter; /* Counter for our table */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for (counter = 1.0; counter < 10.0;counter += 1.0) { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("1/%f = %f\n", counter, RECIPROCAL(counter)); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;} <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code> <br>

## RESPOSTA 
<code>
#include &ltstdio.h&gt <br>
#define RECIPROCAL(number) (1.0 / (number)) <br>
int main() { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float counter; /* Counter for our table */ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for (counter = 1.0; counter < 10.0;counter += 1.0) { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("1/%f = %f\n", counter, RECIPROCAL(counter)); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;} <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0); <br>
}
</code> <br>

### EXPLICAÇÃO: O macro RECIPROCAL esta tentando ser um macro sem parametros que receber uma variavel number que não esta declarada, para esse codigo funcionar, number deveria ser uma variavel declarado globalmente ou ser um parametro de RECIPROCAL.

# Exercise 10-1: Write a macro that returns TRUE if its parameter is divisible by 10 and FALSE otherwise.

## RESPOSTA
<code>
#include &ltstdio.h&gt <br>

#define DIVISIVEL(number) ( ((number % 10) == 0 ) ? 1 : 0) <br>
int main (){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int number = 21;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if (DIVISIVEL(number)){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("divisivel");<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;else {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("nao divisivel");<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  }<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return 0;<br>
}
</code><br>

# Exercise 10-2: Write a macro is_digit that returns TRUE if its argument is a decimal digit.

## RESPOSTA
<code>
#include &ltstdio.h&gt <br>

#define CHECK_DECIMAL(number) (((number) >= 0 && (number) <= 9) ? 1 : 0) <br>

int main (){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;double number = 2; // esse é o valor a ser testado, pode ser tambem um valor não decimal como A <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if (CHECK_DECIMAL(number)){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("DECIMAL"); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;} <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;else { <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("NAO DECIMAL"); <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return 0;<br>
}<br>
</code><br>

# Exercise 10-3: Write a second macro is_hex that returns true if its argument is a hex digit (0-9, A-F, a-f). The second macro should reference the first

## RESPOSTA
<code>
#include &ltstdio.h&gt <br>
#define CHECK_DECIMAL(number) (((number) >= 0 && (number) <=9) ? 1 : 0) <br>
#define CHECK_HEXDECIMAL(number)  (CHECK_DECIMAL(number) || ((number) >= 'A' && (number) <= 'F' ) || ((number) >= 'a' && (number) <= 'f') ? 1 : 0 ) <br>

int main(){ <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int number = 'b'; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("%d", CHECK_HEXDECIMAL(number)); <br>
}
</code>

# Exercise 10-4: Write a preprocessor macro that swaps two integers. (For the real hacker, write one that does not use a temporary variable declared outside the macro.)

## RESPOSTA
<code>

</code>