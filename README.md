# NFAtoDFA
2021-1 Formal language Assignment#3: Convert NFA to DFA

## Process

main -> TokenFactory -> NFA -> NFAtoDFA -> DFA table(result:console)
It is the process of changing the contents of the input file to a token and outputting the NFA table, 
and changing the NFA to DFA and outputting the DFA table.</br></br>
  (1) input file을 파일입출력을 통해 입력으로 받음. (파일에 input.txt, input2.txt, input3.txt)</br>
    ∎ NFA의 입력은 M=(Q, Σ, δ, q0, F) 형태로 들어가므로 입력을 이것으로 받음.</br>
  (2) TokenFactory 객체에서 각각 토큰으로 나누어 vector 배열에 담음.</br>
  (3) 만들어진 vector 배열들을 입력으로 NFA 객체에서 NFA table을 만듦.</br>
  (4) NFA 객체에서 만들어진 NFA table을 입력으로 NFAtoDFA 객체에서 DFA table로 만듦.</br>

## Class

TokenFactory class -> method: doProcessing(run), print token style string</br>
NFA          class -> method: constructor, make table, get table, show table</br>
NFAtoDFA     class -> method: constructor, convert(NFA->DFA), show table(DFA table)</br> 

## Input file
<b>Format</b>
(Token Separated by space) 
```
[non-terminal symbol1] [non-terminal symbol2] ...
[terminal symbol1] [terminal symbol2] ...
[start non-terminal symbol]
[final non-terminal symbol]
[delta-function1];[delta-function2];...
// (functions separated by ';', delta-function element separated by space, transferring symbols are separeated by ',')
```
<b>input.txt</b>
```
q0 q1
0 1
q0
q1
q0 0 q0,q1;q0 1 q0;q1 0 $;q1 1 q0,q1;
```
<b>input2.txt</b>
```
q0 q1 q2 q3 qf
0 1
q0
qf
q0 0 q1,q2;q0 1 q1,q3;q1 0 q1,q2;q1 1 q1,q3;q2 0 qf;q2 1 $;q3 0 $;q3 1 qf;qf 0 qf;qf 1 qf;
```
<b>input3.txt</b>
```
p q r
a b
q
r
p a q,r;p b q;q a $;q b p;r a p;r b p,r;
```
## Output
result of input1.txt
![image](https://user-images.githubusercontent.com/54761791/163568694-877af027-0be0-40fd-809b-7ac70cca8c18.png)
result of input2.txt
![image](https://user-images.githubusercontent.com/54761791/163568710-6695d44f-1639-4906-913e-b3c656badc26.png)
result of input3.txt
![image](https://user-images.githubusercontent.com/54761791/163568732-ac486db7-ad7e-4e6e-8900-5b6c283e1a6a.png)
