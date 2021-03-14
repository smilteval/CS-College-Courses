<?php

function validateStr($str)
{
    $str = trim($str);
    $str = stripcslashes($str);
    $str = htmlspecialchars($str);

    return $str;
}

$errors = []; //array containing input errors
$success = false;

$usernamePattern = "/[a-zA-Z]{1}_[a-zA-Z]+$/"; //first initial_lastname

if (isset($_POST["submit"])) {

    //validate username and password to prevent malicious code
    $username = validateStr($_POST["username"]);
    $password = validateStr($_POST["password"]);

    $file = "accounts.json";
    $accounts = file_get_contents($file); //get the contents of all accounts
    $accounts = json_decode($accounts); //turn that content into array

    //handle empty fields
    if (empty($_POST["username"])) {
        $errors["username"] = "Missing username";
    } else {
        //validate format
        if (!preg_match($usernamePattern, $username)) {
            $errors["username"] = "Format is incorrect. Use first initial_lastname.";
        }
    }

    if (empty($_POST["password"])) {
        $errors["password"] = "Missing password";
    }

    //if there are no errors, append the account to the accounts array
    if (count($errors) == 0) {
        $success = true;

        //store the new account into an array
        $new_account = array("username" => $username, "password" => $password);

        array_push($accounts, $new_account); //append new account to the accounts array
        $accounts = json_encode($accounts); //turn the new array back into json
        file_put_contents($file, $accounts); //place the json into the file
    }
}
