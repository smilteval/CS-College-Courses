<?php
    mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

    try{
        define("DOMAIN", "localhost");
        define("USERNAME", "root");
        define("PWD", "");
        define("DATABASE", "PREMIERE");

        $conn = new mysqli(DOMAIN, USERNAME, PWD, DATABASE);
        $conn -> set_charset("utf8mb4");
    }
    catch(Exception $e){
        error_log($e->getMessage());
        exit("Error connecting to database");
    }