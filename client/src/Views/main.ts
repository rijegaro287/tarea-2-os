import { sendImage, testAPI } from "./request.js";

document.addEventListener('DOMContentLoaded', async () => {
  const uploadButton = document.getElementById('upload-button') as HTMLButtonElement;
  const fileInput = document.getElementById('file-input') as HTMLInputElement;

  const uploadedImage = document.getElementById('uploaded-image') as HTMLImageElement;
  const processedImage = document.getElementById('processed-image') as HTMLImageElement;

  const processButton = document.getElementById('process-button') as HTMLButtonElement;
  const cancelButton = document.getElementById('cancel-button') as HTMLButtonElement;

  if (
    !uploadButton || !fileInput || !processButton ||
    !cancelButton || !uploadedImage || !processedImage
  ) {
    await alert('Error: Could not find all required elements. \nReloading...');
    return window.location.reload();
  }

  if (!fileInput.files) {
    processButton.disabled = true;
    cancelButton.disabled = true;
  }

  testAPI().then((response) => {
    if (response.status !== 200) {
      alert('Error: Could not connect to server.');
    }
  });


  uploadButton.addEventListener('click', () => { fileInput.click() });


  fileInput.addEventListener('change', () => {
    if (!fileInput.files) { return; }

    const file = fileInput.files[0];
    uploadedImage.src = URL.createObjectURL(file);

    processButton.disabled = false;
    processButton.scrollIntoView();
  });


  processButton.addEventListener('click', async () => {
    if (!fileInput.files) { return; }

    const image = fileInput.files[0];

    const imageFormData = new FormData();
    imageFormData.append('file', image);

    await sendImage(imageFormData)
      .then((response) => {
        console.log(response);
        return response.json();
      })
      .then((data) => {
        console.log(data);
      });
  });
});