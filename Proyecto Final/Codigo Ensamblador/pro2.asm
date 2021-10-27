include macpro2.asm
.model small

; -------------- SEGMENTO DE PILA -----------------
.stack

; -------------- SEGMENTO DE DATOS -----------------
.data
titulo db 0ah, 0dh, '----- Menu Principal -----' ,'$'
encabezado db 0ah, 0dh, '1) Derivar Funcion',0ah, 0dh, '2) Integrar Funcion',0ah, 0dh, '3) Ingresar Funciones',0ah, 0dh, '4) Imprimir Funciones Ingresadas',0ah, 0dh, '5) Graficar',0ah, 0dh, '6) Resolver Ecuacion',0ah, 0dh, '7) Enviar a arduino',0ah, 0dh, '8) Salir',0ah, 0dh, '9) Cargar Archivo',0ah, 0dh, '0) Seleccionar id Funcion', '$' 
salto db 0ah, 0dh, '$' ,'$'
ingreseRuta db 0ah, 0dh, 'Ingrese una ruta de un Archivo', 0ah, 0dh, 'Ejemplo: Entrada.txt','$'

err1 db 0ah,0dh, 'Error al abrir el archivo puede que no exista' , '$'
err2 db 0ah,0dh, 'Error al cerrar el archivo' , '$'
err3 db 0ah,0dh, 'Error al escribir en el archivo' , '$'
err4 db 0ah,0dh, 'Error al crear en el archivo' , '$'
err5 db 0ah,0dh, 'Error al leer en el archivo' , '$'

bufferentrada db 50 dup('$')
handlerentrada dw ?
bufferInformacion db 500 dup('$')

inicioFuncion db 20 dup('$')
finFuncion db 20 dup('$')
funcion db 50 dup('$')
numero db 2 dup('$')

idMensaje db 0ah,0dh, 'Ingrese el id de la funcion' , '$'


;----------------SEGMENTO DE CODIGO---------------------
.code
main proc
	Menu:
		print titulo
		print encabezado
		print salto
		getChar
		cmp al, 57
		je CargarArchivo
		cmp al, 48
		je seleccionarFuncion
		cmp al, 56
		je Salir
		jmp Menu

	CargarArchivo:
		print salto
		print ingreseRuta
		print salto
		limpiar bufferentrada, SIZEOF bufferentrada, 24h ; 24h = $
		obtenerRuta bufferentrada
		abrir bufferentrada, handlerentrada
		limpiar bufferInformacion, SIZEOF bufferInformacion, 24h
		leer handlerentrada, bufferInformacion, SIZEOF bufferInformacion
		cerrar handlerentrada
		;print bufferInformacion

		separacionFunciones bufferInformacion
		limpiar funcion, SIZEOF funcion, 24h
		jmp Menu

	seleccionarFuncion:
		print idMensaje
		print salto
		limpiar numero, SIZEOF numero, 24h
		obtenerTexto numero

		StringToInt numero ;ax tiene el valor numerico del arreglo

		dec ax

		limpiar funcion, SIZEOF funcion, 24h
		obtenerFuncion ax, funcion, bufferInformacion
		print funcion

		getChar
		jmp Menu

	Error1:
		print salto
		print err1
		getChar
		jmp Menu

	Error2:
		print salto
		print err2
		getChar
		jmp Menu
	
	Error3:
		print salto
		print err3
		getChar
		jmp Menu
	
	Error4:
		print salto
		print err4
		getChar
		jmp Menu

	Error5:
		print salto
		print err5
		getChar
		jmp Menu

	Salir:
		close

main endp
end main