<!doctype html>
<html lang="en">
  <head>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <meta charset="utf-8">
    <title>Proyecto Artefactos</title>

    <style>
      .bd-placeholder-img {
        font-size: 1.125rem;
        text-anchor: middle;
        -webkit-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
      }

      @media (min-width: 768px) {
        .bd-placeholder-img-lg {
          font-size: 3.5rem;
        }
      }
    </style>
    <link href="cover.css" rel="stylesheet">
    <script src="func.js"></script>
  </head>
  <body class="text-center">
    <header class="masthead mb-auto">
        <div class="inner">
            <h3 class="masthead-brand">Agua</h3>
        </div>
    </header>
    <?php

        $myfile = fopen("funcion.txt", "w") or die("Unable to open file!");
        $txt = "asi";
        fwrite($myfile, $txt);

        fclose($myfile);

    ?>
    
    <div class="btn-group" role="group" aria-label="Basic example">
            <form action="">
            <button type="submit" class="btn btn-secondary" formaction="agua_encendida.php">Activo</button>
            <button type="submit" class="btn btn-secondary" formaction="agua_apagada.php" >Inactivo</button>
            </form>
    </div>
    <p id="agua" ></p>

    <header class="masthead mb-auto">
            <div class="inner">
              <h3 class="masthead-brand">Luz</h3>
            </div>
    </header>

    <div class="btn-group" role="group" aria-label="Basic example">
    <form action="">
            <button type="submit" class="btn btn-secondary" formaction="bomba_encendida.php">Activo</button>
            <button type="submit" class="btn btn-secondary" formaction="bomba_apagada.php" >Inactivo</button>
        </form>
    </div>
    <p id="luz" style="display:none;"></p>
</div>
</body>
</html>
