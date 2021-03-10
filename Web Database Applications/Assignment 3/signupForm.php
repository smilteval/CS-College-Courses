<?php
include 'handleSignupForm.inc.php';
?>

<!DOCTYPE html>
<html lang="en">

<head>
  <title>Sign-Up</title>
  <style>
    .error-text {
      color: red;
      font-size: small;
    }

    .success-text {
      color: green;
    }
  </style>
</head>

<body>
  <form action="signupForm.php" method="POST">
    <p>
      <label>Username:
        <input type="text" name="username" value="<?php echo (isset($_POST['username'])) ? $_POST['username'] : '' ?>" />

        <p class="error-text">
          <?php echo (isset($errors['username'])) ? $errors['username'] : ''; ?>
        </p>

      </label>
    </p>
    <p>
      <label>Password:
        <input type="password" name="password" value="<?php echo (isset($_POST['password'])) ? $_POST['password'] : '' ?>" />

        <p class="error-text">
          <?php echo (isset($errors['password'])) ? $errors['password'] : ''; ?>
        </p>

      </label>
    </p>
    <p>
      <input type="submit" name="submit" value="Sign-up" />
    </p>
    <p class="success-text">
      <?php
      echo ($success == true ? "You signed up successfully!" : "");
      ?>
    <p>
  </form>
</body>

</html>