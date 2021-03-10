<!-- Process data -->

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

    //validating username to prevent malicious code
    $username = validateStr($_POST["username"]);
    $password = validateStr($_POST["password"]);

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

    //clear the form once it's submitted
    if (count($errors) == 0) {
        $success = true;
    }

    //get the contents of accounts
    $file = "accounts.json";
    $accounts = file_get_contents($file);

    //turn that content into array
    $accounts = json_decode($accounts);

    //store the new account into an array
    $new_account = array("username" => $username, "password" => $password);

    //append new account to the accounts array
    array_push($accounts, $new_account);

    //turn the new array back into json
    $accounts = json_encode($accounts);

    //place the json into the file
    file_put_contents($file, $accounts);
}

?>