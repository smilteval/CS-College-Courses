<?php
include 'handleSignupForm.inc.php';
?>

<!DOCTYPE html>

<head>
  <link rel="stylesheet" href="signupStyle.css" />
  <title>Sign-Up</title>
</head>

<body>
  <div class="vid-container">
    <video class="bgvid" autoplay="autoplay" muted="muted" preload="auto" loop>
      <source src="https://static.videezy.com/system/resources/previews/000/007/313/original/Plexus.mp4">
    </video>
    <div class="inner-container">
      <video class="bgvid inner" autoplay="autoplay" muted="muted" preload="auto" loop>
        <source src="https://static.videezy.com/system/resources/previews/000/007/313/original/Plexus.mp4">
      </video>
      <form action="signupForm.php" method="POST">
        <h2> Sign Up </h2>
        <p>
          <input type="text" name="username" placeholder="Username (Ex. f_lastname)" value="<?php echo (isset($_POST['username'])) ? $_POST['username'] : '' ?>" />
        <p class="error-text">
          <?php echo (isset($errors['username'])) ? $errors['username'] : ''; ?>
        </p>
        </p>
        <p>
          <input type="password" name="password" placeholder="Password" value="<?php echo (isset($_POST['password'])) ? $_POST['password'] : '' ?>" />
        <p class="error-text">
          <?php echo (isset($errors['password'])) ? $errors['password'] : ''; ?>
        </p>
        </p>
        <p>
          <button type="submit" name="submit"> Sign up </button>
        </p>
        <p class="success-text">
          <?php echo ($success ? "You signed up successfully!" : ""); ?>
        <p>
        <p>Already have an account? <a href="loginForm.php"><span>Login</span></a></p>
      </form>
    </div>
  </div>
</body>

</html>