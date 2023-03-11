# Git
## Crear un token de Github
Para subir tus archivos a github necesitas "iniciar seción", basicamente autentificarte, si quieres autentificarte con tu correo y contraseña también se puede, pero en caso de que no, puedes generar un token: https://github.com/settings/tokens. Una vez tengas generado tu token, este lo podrás usar para autentificarte al subir archivos a tu repositorio de Github (_guarden su token porque una vez lo generan por primera vez, ya no lo van a volver a ver a no ser que lo vuelvan a generar_).
## Setup de Git para usar Github

``` bash
git config --global user.name "Tu nombre"
git config --global user.email "Tu correo"
```
## Guía básica para subir archivos a Github
``` bash
git init # Inicializar repositorio de git
git add file.txt # Agregar tu archivo de texto a git
git commit -m "Agregado archivo file.txt" # Capturar los cambios hechos
git branch -M master # Seleccionar la rama 
git remote add origin $url_repositorio # Añadir el repositorio donde vas a subir tus archivos. Este paso solo es necesario una vez.
git push -u origin $branch_name # Subir el commit a tu rama
```
## Documentación
+ Guía básica para manejar un repositorio: https://github.com/skills/introduction-to-github
+ Index cursos de Git: https://skills.github.com/
# Inglés
## Documentación:
+ Tutoriales básicos: https://www.w3schools.com/cpp/
+ Referencia oficial de las librerías estandar en c++: https://cplusplus.com/
+ Explicaciones de temas con implementaciones: https://www.geeksforgeeks.org/
# Youtube
+ Tutorial full c++ 6h: https://www.youtube.com/watch?v=-TkoO8Z07hI
 + https://youtu.be/yfppUS0b0P8
 + Como depurar en CLion: https://www.youtube.com/watch?v=Au3r4n5zlls
# Español
## Youtube: 
+ Full curso c++: https://www.youtube.com/watch?v=dJzLmjSJc2c&list=PLWtYZ2ejMVJlUu1rEHLC0i_oibctkl0Vh
+ Estructuras de datos en c: https://www.youtube.com/watch?v=oQ0WkIdr73E&list=PLTd5ehIj0goMTSK7RRAPBF4wP-Nj5DRvT
