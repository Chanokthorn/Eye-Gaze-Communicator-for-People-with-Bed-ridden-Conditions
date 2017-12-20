<h1>Eye Gaze Communicator for People with Bed-ridden Conditions
</h1>
<p>*I worked on the gaze detection part of this project</p>
<p> The gaze detection is made by using multiple models and libraries avaiable online, which will be referenced in the description of code<p>
<div>
  <p> The code is made primarily using OpenCV2. The first part is to extract important features from the face using a model made by Adrian Rosebrock
  shown in <a href="https://www.pyimagesearch.com/2017/04/03/facial-landmarks-dlib-opencv-python/">This link</a>
  <p> Next I used OpenCV to convert eye features into a thresholded pictures for ease of iris detection</p>
  <p> The iris detection is done by using Hough Transformation in OpenCV, but the algorithm only works on the horizontal direction
  of the eye gaze</p>
  <p> For upward direction, it is more efficient to find the average sum of pixel value of the lower half the thresholded eye picture,
  which will increase when the user gaze upward, although gazing downward is out of the scope since it is very similar to closing the eye</p>
  <h5>***this project is presented by Dr.Pitchaya Sitthi-amorn and will not be possible without the help of Thananop Kobchaisawat who kindly
  gave the resources and advices neccessary for the gaze detection</h5>
</div>
