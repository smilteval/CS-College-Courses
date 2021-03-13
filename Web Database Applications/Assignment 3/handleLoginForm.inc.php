<?php

function validateStr($str)
{
    $str = trim($str);
    $str = stripcslashes($str);
    $str = htmlspecialchars($str);

    return $str;
}

$errors = []; //array containing input errors

$usernameFound = false;
$passwordFound = false;
$accountNotFound = false;

if (isset($_POST["submit"])) {

    //validate username and password to prevent malicious code
    $username = validateStr($_POST["username"]);
    $password = validateStr($_POST["password"]);

    //create an array with the info we want to match
    $matchingAccount = array("username" => $username, "password" => $password);

    //handle empty fields
    if (empty($_POST["username"])) {
        $errors["username"] = "Missing username";
    }

    if (empty($_POST["password"])) {
        $errors["password"] = "Missing password";
    }

    //get the contents of accounts
    $file = "accounts.json";
    $accounts = file_get_contents($file);

    //turn that content into an associative array
    $accounts = json_decode($accounts, true);

    //check if our desired account is inside of the accounts array
    if (in_array($matchingAccount, $accounts)) {
        header("Location: welcome.php?username=$username");
        exit();
    } 
    else if (count($errors) == 0) {
        $errors["accountNotFound"] = "The user does not exist, please check your username and password";
    }
}
