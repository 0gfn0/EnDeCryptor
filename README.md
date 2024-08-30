<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- PROJECT LOGO
<br />
<div align="center">
  <a href="https://github.com/0gfn0/EnDeCryptor">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
 </a>
-->
<h3 align="center">EnDeCryptor</h3>

  <p align="center">
    EnDeCryptor It is a simple encoder and decoder that supports 3 encryption options: Caesar cipher, Vigener cipher, and public key (RSA).
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
<div align="center">
[![MainMenu Product][MainMenu-screenshot]](image.png)
</div>
EnDecrypter supports 3 encryption options: Caesar cipher, Vigener cipher, and public key (RSA).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running app follow these simple example steps.

### Installation

1. Download a newest version of wxWidgets at [wxWidgets](https://www.wxwidgets.org/downloads/)
2. Download and install newest version of CMake at [CMake](https://cmake.org/download/)
3. Clone the repo
   ```sh
   git clone https://github.com/0gfn0/EnDeCryptor.git
   ```
3. Unzip wxWidgets in path .../EnDeCryptor/External/wxWidgets
4. Open cmd at folder .../EnDeCryptor and run mkdir build
   ```sh
   .../EnDeCryptor> mkdir build
   ```
5. Go to the build folder using the cmd
   ```sh
   .../EnDeCryptor> cd build
   ```
6. Run cmake file in build folder
   ```sh
   .../EnDeCryptor/build> cmake ..
   ```
7. After a successful assembly, run the project build
   ```sh
   .../EnDeCryptor/build> cmake --build .
   ```
8. Now you can find the EnDeCryptor.exe file along the path
   ```sh
   .../EnDeCryptor/build/debug
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage!

You can encrypt and decrypt by 3 various cipher. Let's see how to encrypt a message using a public key.
1. Open EnDeCryptor.exe
[![MainMenu][MainMenu-screenshot]](image1.png)
2. Choose and press Encrypt button, you will see all posible methods of encryption, press RSA button
[![OptionMenu][OptionMenu-screenshot]](image2.png)
3. Type the message you want to encrypt
[![RSA-Text][RSA-Text-screenshot]](image3.png)
4. Enter the part of the public key (e - open exp), it must be a prime number. For example e = 17.
[![Enumber][Enumber-screenshot]](image4.png)
5. Enter the part of the public key (n - module). For example n = 3233
[![Nnumber][Nnumber-screenshot]](image5.png)
6. Now you get encrypted message.
[![Message][Message-screenshot]](image6.png)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Support output and input files
- [ ] More variable cipher

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[MainMenu-screenshot]: Assets/image1.png
[OptionMenu-screenshot]: Assets/image2.png
[RSA-Text-screenshot]: Assets/image3.png
[Enumber-screenshot]: Assets/image4.png
[Nnumber-screenshot]: Assets/image5.png
[Message-screenshot]: Assets/image6.png


