package main

import (
	"fmt"
	"net/http"
	"html/template"
)

func index(w http.ResponseWriter,r *http.Request){
	template, err := template.ParseFiles("templates/index.html")
	if err != nil{
		fmt.Fprintf(w,"Pagina no encontrada")
	}	else{
		template.Execute(w,nil)
	}
}

func main(){
	http.HandleFunc("/",index)
   fmt.Println("Sistemas Operativos 1")
   http.ListenAndServe(":8080",nil)
}