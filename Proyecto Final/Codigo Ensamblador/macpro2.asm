print macro buffer ;imprime cadena
push ax
push dx
	mov ax, @data
	mov ds,ax
	mov ah,09h ;Numero de funcion para imprimir buffer en pantalla
	mov dx,offset buffer ;equivalente a que lea dx,buffer, inicializa en dx la posicion donde comienza la cadena
	int 21h
pop dx
pop ax
endm

close macro ;cierra el programa
	mov ah, 4ch ;Numero de funcion que finaliza el programa
	xor al,al
	int 21h
endm

getChar macro  ;obtiene el caracter y se almacena el valor en el registro al
	mov ah,01h ; se guarda en al en codigo hexadecimal
	int 21h
endm

obtenerTexto macro buffer
LOCAL ObtenerChar, endTexto
	xor si,si ; xor si,si =	mov si,0
	
	ObtenerChar:
		getChar
		cmp al,0dh ; ascii de salto de linea en hexa
		je endTexto
		mov buffer[si],al ;mov destino, fuente
		inc si ; si = si + 1
		jmp ObtenerChar

	endTexto:
		mov al,24h ; asci del signo dolar $
		mov buffer[si], al  
endm

separacionFunciones macro arreglo
LOCAL Mientras, Fin, AsignarFin
	xor si, si
	xor al, al
	xor di, di

	mov inicioFuncion[di], 0

		Mientras:
			cmp al, 24h
			je Fin
			;arreglo[1] = al
			mov al, arreglo[si]
			cmp al, 59 ;verificamos que el caracter sea ;
			je AsignarFin
			inc si
			jmp Mientras

		AsignarFin:
			xor bx, bx
			mov bx, si
			dec bx
			mov finFuncion[di], bl
			;si = si + 1
			inc si
			mov al, arreglo[si]
			cmp al, 24h
			je Fin
			inc si
			inc di

			xor bx, bx
			mov bx, si
			mov inicioFuncion[di], bl
			jmp Mientras

		Fin:

endm

obtenerFuncion macro id, arreglo, funciones
LOCAL Mientras, Fin
	xor si, si
	xor di, di

	mov di, id

	xor bx, bx
	mov bl, inicioFuncion[di]
	;bl tiene la posicion inicial
	mov si, bx ;si tiene la posicion inicial

	xor bx, bx
	mov bl, finFuncion[di]

	;si posicion inicial, bx tiene la posicion final
	xor di, di
	inc bx
	xor ax, ax

	Mientras:
		cmp si, bx
		je Fin
		mov al,funciones[si]
		mov arreglo[di], al
		inc si
		inc di
		jmp Mientras

	Fin:

endm

;-----------------Abrir y Guardar un archivo----------------

obtenerRuta macro buffer
LOCAL ObtenerChar, endTexto
	xor si,si ; xor si,si =	mov si,0
	
	ObtenerChar:
		getChar
		cmp al,0dh ; ascii de salto de linea en hexa
		je endTexto
		mov buffer[si],al ;mov destino, fuente
		inc si ; si = si + 1
		jmp ObtenerChar

	endTexto:
		mov al,00h ; asci del caracter nulo
		mov buffer[si], al  
endm

abrir macro buffer,handler

	mov ah,3dh ;funcion para abrir fichero 
	mov al,02h ;010b Acceso de lectura/escritura. 010b 
	lea dx,buffer ;carga la dirección de la fuente (buffer) a dx 
	int 21h ;ejecutamos la interrupción 
	jc Error1 ;salta si el flag de acarreo = 1
	mov handler,ax ;sino hay error  en ax devuelve un handle para acceder al fichero 

endm

cerrar macro handler
	
	mov ah,3eh
	mov bx, handler
	int 21h
	jc Error2
	mov handler,ax

endm

leer macro handler,buffer, numbytes
	
	mov ah,3fh ;interrupción para leer 
	mov bx,handler ;copiamos en bx el handler,referencia al fichero
	mov cx,numbytes ;numero de bytes a leer, tamaño del arreglo que guarda el contenido 
	lea dx,buffer ;carga la dirección de la variable buffer a dx
	int 21h
	jc  Error5
	;en el buffer se guarda la información

endm
;en el macro limpiar vamos a limpiar el arreglo con $
limpiar macro buffer, numbytes, caracter
LOCAL Repetir
	xor si,si ; colocamos en 0 el contador si
	xor cx,cx ; colocamos en 0 el contador cx
	mov	cx,numbytes ;le pasamos a cx el tamaño del arreglo a limpiar 

	Repetir:
		mov buffer[si], caracter ;le asigno el caracter que le estoy mandando 
		inc si ;incremento si = si++;
		Loop Repetir ;se va a repetir hasta que cx sea 0 
endm

crear macro buffer, handler
	
	mov ah,3ch ;función para crear fichero
	mov cx,00h ;fichero normal 
	lea dx,buffer ;carga la dirección de la variable buffer a dx
	int 21h
	jc Error4
	mov handler, ax ;sino hubo error nos devuelve el handler 

endm

escribir macro handler, buffer, numbytes

	mov ah, 40h ;función de escritura del archivo 
	mov bx, handler ;en bx copiamos el handler, 
	mov cx, numbytes ;numero de bytes a escribir 
	lea dx, buffer ;carga la dirección de la variable buffer a dx
	int 21h ;ejecutamos la interrupción 
	jc Error3

endm

;-----------Codigo para convertir valores int o string --------------------------

StringToInt macro string
LOCAL Unidades,Decenas,salir, Centenas

	sizeNumberString string; en la variable bl me retorna la cantidad de digitos
	xor ax,ax
	xor cx,cx

	cmp bl,1
	je Unidades

	cmp bl,2
	je Decenas

	cmp bl,3
	je Centenas



	Unidades:
		mov al,string[0]
		SUB al,30h
		jmp salir

	Decenas:

		mov al,string[0]
		sub al,30h
		mov bl,10
		mul bl


		xor bx,bx
		mov bl,string[1]
		sub bl,30h

		add al,bl

		jmp salir

;bl 1111 1111 ->255
; 0 - 999 
; bx 1111 1111 1111 1111 -> 65535
	Centenas:
	    ;543
		mov al,string[0] ;[0] -> 53 -> 5 en ascii
		sub al,30h;  -> 53-48 = 5 => Ax=5 => Ax-Ah,Al
		mov bx,100;  -> bx = 100
		mul bx; -> ax*bx = 5*100 = 500
		mov cx,ax; cx = 500
		;dx = Centenas

		xor ax,ax ; ax = 0
		mov al,string[1] ;[1] -> 52 -> 4 en ascii
		sub al,30h ; -> 52-48 = 4 => Ax=4 => Ax-Ah,Al
		mov bx,10 ;  -> bx = 10
		mul bx ; -> ax*bx = 4*10 = 40

		xor bx,bx
		mov bl,string[2] ;[2] -> 51 -> 3 en ascii
		sub bl,30h ; -> 51-48 = 3 => Ax=3 => Ax-Ah,Al

		add ax,bx ; ax = 3 + 40
		add ax,cx ; ax = 43 + 500 = 543
		
		jmp salir

	salir:
	

endm

;1.1
;[49][46][49]
;ax = entera
;bx = decimal
IntToString macro num, number ; ax 1111 1111 1111 1111 -> 65535
LOCAL Inicio,Final,Mientras,MientrasN,Cero,InicioN
push si
push di
limpiar number,SIZEOF number,24h
mov ax,num ; ax = numero entero a convertir 23
cmp ax,0 
je Cero
xor di,di
xor si,si
jmp Inicio

;ax = 123

Inicio:
	
	cmp ax,0 ;ax = 0
	je Mientras
	mov dx,0 
	mov cx,10 
	div cx ; 1/10 = ax = 0 dx = 2
	mov bx,dx 
	add bx,30h ; 1 + 48 = ascii 
	push bx 
	inc di	; di = 3
	jmp Inicio

Mientras:
	;si = 0 , di = 3
	cmp si,di 
	je Final
	pop bx 
	mov number[si],bl 
	inc si 
	;si = 2 di = 3
	jmp Mientras

Cero:
 mov number[0],30h
 jmp Final

Final:
pop di
pop si


endm

sizeNumberString macro string
LOCAL LeerNumero, endTexto
	xor si,si ; xor si,si =	mov si,0
	xor bx,bx

	LeerNumero:
		mov bl,string[si] ;mov destino, fuente
		cmp bl,24h ; ascii de signo dolar
		je endTexto
		inc si ; si = si + 1
		jmp LeerNumero

	endTexto:
		mov bx,si

endm

FloatToString macro entera, decimal, number

LOCAL Inicio,Final,MientrasEntero,Cero,FinalEntero, InicioDecimal, MientrasDecimal
push si
push di

limpiar number,SIZEOF number,24h
mov ax,entera ; ax = numero entero a convertir
cmp ax,0 
je Cero
xor di,di
xor si,si
jmp Inicio


Inicio:
	;514
	cmp ax,0 ; ax = 0 -> Brinca a mientras
	je MientrasEntero
	mov dx,0 ;dx = 0
	mov cx,10 ; cx = 10
	div cx ; ax / 10 ->   resultado => ax=0 ! residuo => dx = 1 
	mov bx,dx ; bx = residuo de la division = 1
	add bx,30h ; residuo => residuo + 30h => numero convertido a su valor en ascii
	push bx ; numero convertido a su valor en ascii en la pila [1] = 49 415
	inc di	; di = di + 1
	jmp Inicio

MientrasEntero:
;514
	cmp si,di ; di = 2 ! si = 1
	je FinalEntero
	pop bx ; bx = [0] = 52
	mov number[si],bl ; numero[1] = 52
	inc si ; si =1
	jmp MientrasEntero

Cero:
 mov number[0],30h
 jmp Final

FinalEntero:
;12.4
;si = 2
;Se termina de convertir la parte entera a texto
;Se asigna el punto decimal

mov number[si],46
inc si
inc di

;si = 3
;di = 3

mov ax,decimal ; ax = numero entero a convertir
cmp ax,0 
je CeroDecimal
jmp InicioDecimal


InicioDecimal:
	;514
	cmp ax,0 ; ax = 0 -> Brinca a mientras
	je MientrasDecimal
	mov dx,0 ;dx = 0
	mov cx,10 ; cx = 10
	div cx ; ax / 10 ->   resultado => ax=0 ! residuo => dx = 1 
	mov bx,dx ; bx = residuo de la division = 1
	add bx,30h ; residuo => residuo + 30h => numero convertido a su valor en ascii
	push bx ; numero convertido a su valor en ascii en la pila [1] = 49 415
	inc di	; di = di + 1
	jmp InicioDecimal

MientrasDecimal:
;514
	cmp si,di ; di = 7 ! si = 4
	je Final
	pop bx ; bx = [0] = 52
	mov number[si],bl ; numero[1] = 52
	inc si ; si =1
	jmp MientrasDecimal

CeroDecimal:
 mov number[si],30h
 jmp Final


Final:


pop di
pop si


endm


DivisionConDecimal macro num1, num2 ; 13 / 5
LOCAL ForAux,Final

	mov ax,num1 ;13
	mov bx,num2 ; 5
	div bx ;13/5 -> ax = 2 ! dx = 3
	mov residuo,dx
	mov resultadorDivisionEntero,ax ; 2

	ForAux:
		cmp residuo,0
		je Final
		mov bx,10 ; bx = 10
		mov ax, residuo ;ax = 3
		mul bx ; ax = 10*3 = 30
		mov bx,num2 ;bx = 5
		div bx ; 30/5
		mov residuo,dx
		mov resultadorDivisionDecimal,ax
		jmp ForAux

Final:

endm


agregarExt macro ruta

LOCAL Mientras, FinMientras
	xor si,si ; xor si,si =	mov si,0
	;hola
	;0 -> h ascii
	;
	Mientras:
		mov al,ruta[si] ;mov destino, fuente
		inc si ; si++
		cmp al,00h ; ascii de signo nulo
		je FinMientras
		jmp Mientras

	FinMientras:
		;ruta[4]
		dec si
		mov ruta[si], 2Eh ; .
		inc si
		mov ruta[si], 78h ; x
  		inc si
  		mov ruta[si], 6Dh ; m
  		inc si
  		mov ruta[si], 6Ch ; l
  		inc si
  		mov ruta[si], 00h ;caracter nulo al final

endm

ContarUnidades macro numero
LOCAL Mientras, FinMientras

xor si,si ;registro de 16 bits
xor bx,bx

	Mientras:
	mov al,numero[si]
	cmp al,24h ;cuando encontremos $ dejamos el contador
	je FinMientras
	inc si
	jmp Mientras

	FinMientras:
	;si el contador vale 2 el numero es > 9 si el contador vale 1 el numero <10
	mov bx,si ;bl nos indica si son unidades o si son decenas
	; como sabemos que el numero  <2 sabemos que el resultado de guarda en bl
endm

TextoAEntero macro texto ;en el registo al se va a guardar el numero convertido
LOCAL Unidades, Decenas, Final
xor al,al
ContarUnidades texto
;bl me indica si el numero tiene unidades o tiene decenas

cmp bl,1
je Unidades
cmp bl,2
je Decenas
jmp Final

	Unidades:
		;texto[0] -> numero de unidades en ascii
		mov al,texto[0]
		sub al, 48 ; al = al - 48
		jmp Final


	Decenas:
		
		;texto[0]-> numero de decenas en ascii
		;texto[1]-> numero de unidades en ascii
		mov al,texto[0]
		sub al,48 ; ya tengo las decenas en su valor decimal 45 -> 4
		mov bl,10
		mul bl ; al = al * bl
		;al = 40

		xor bl,bl
		mov bl, texto[1]
		sub bl, 48 ; bl = 5

		add al,bl ;  al = 40 +5

		jmp Final

	Final:

endm

EnteroATexto macro numero, texto
LOCAL Unidades, Decenas, Final
xor al,al

mov al,numero
cmp al,9 ;numero > 9 tiene decenas
ja Decenas
jmp Unidades

	Unidades:
		add al,48 ;2+48 = 50
		mov texto[0],al
		jmp Final
	


	Decenas:

		xor bl,bl
		;al tiene el numero completo 45
		mov bl,10

		div bl ; 45/10 al = 4 y ah = 5

		add al,48
		mov texto[0],al
		
		add ah,48
		mov texto[1],ah

		jmp Final



	Final:

endm


AgregarId macro arreglo, global
LOCAL Mientras, FinMientras, FinMientras2

	xor si,si
	xor di,di
	Mientras:
		mov al,global[si] ;mov destino, fuente
		inc si ; si++
		cmp al, 36 ; ascii de signo nulo
		je FinMientras
		jmp Mientras

	FinMientras:
		mov di,1
		mov al, arreglo[di] ;mov destino, fuente
		dec si
		mov global[si], al
		inc di
		inc si
		cmp al, 36 ; ascii de signo nulo
		je FinMientras2
		jmp FinMientras

	FinMientras2:
		mov al, 59
		mov global[si], al			

endm