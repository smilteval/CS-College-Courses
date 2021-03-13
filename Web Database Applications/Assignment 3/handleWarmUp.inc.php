<?php

function validateStr($str)
{
    $str = trim($str);
    $str = stripcslashes($str);
    $str = htmlspecialchars($str);

    return $str;
}

$errors = []; //array containing input errors

if (isset($_POST["submit"])) {

    //handle empty fields
    if (empty($_POST["username"])) {
        $errors["username"] = "Missing username";
    }

    if (empty($_POST["password"])) {
        $errors["password"] = "Missing password";
    }

    //validate username to prevent malicious code
    $username = validateStr($_POST["username"]);

    //clear the form once it's submitted
    if (count($errors) == 0) {
        header("Location: warmupForm.php");
        exit();
    }
}
