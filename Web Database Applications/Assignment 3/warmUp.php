<?php
include 'handleWarmUp.inc.php';
?>

<!DOCTYPE html>
<html lang="en">

<head>
  <title>Warm Up</title>
  <style>
    .error-text {
      color: red;
      font-size: small;
    }
  </style>
</head>

<body>
  <form action="warmUp.php" method="POST">
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
      <input type="submit" name="submit" value="Send info" />
    </p>
  </form>
</body>

</html>