<?php
include "handleLoginForm.inc.php";
?>

<!DOCTYPE html>

<head>
  <title>Log-In</title>
  <style>
    .error-text {
      color: red;
      font-size: small;
    }
  </style>
</head>

<body>
  <form action="loginForm.php" method="POST">
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
      <input type="submit" name="submit" value="Log-In" />
    </p>
    <p class="error-text">
      <?php echo (isset($errors['accountNotFound'])) ? $errors['accountNotFound'] : ''; ?>
    <p>
  </form>
</body>

</html>