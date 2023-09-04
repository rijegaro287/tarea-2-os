import { decodeResponseBody, sendImage, testAPI } from "./request.js";

document.addEventListener('DOMContentLoaded', async () => {
  const uploadButton = document.getElementById('upload-button') as HTMLButtonElement;
  const fileInput = document.getElementById('file-input') as HTMLInputElement;

  const selectedImagesContainer = document.getElementById('selected-images-container') as HTMLElement;

  const processButton = document.getElementById('process-button') as HTMLButtonElement;
  const cancelButton = document.getElementById('cancel-button') as HTMLButtonElement;

  const progressBar = document.getElementById('progress-bar') as HTMLElement;

  let sendingFiles = false;

  if (
    !uploadButton || !fileInput || !processButton ||
    !cancelButton || !selectedImagesContainer || !progressBar
  ) {
    await alert('Error: Could not find all required elements. \nReloading...');
    return window.location.reload();
  }

  processButton.disabled = true;
  cancelButton.disabled = true;

  testAPI().then(async (response) => {
    if (response.status !== 200) {
      alert('Error: Could not connect to server.');
    }

    const responseBody = await decodeResponseBody(response);
    console.log(responseBody);
  });


  uploadButton.addEventListener('click', () => { fileInput.click() });


  fileInput.addEventListener('change', () => {
    if (!fileInput.files) { return; }

    selectedImagesContainer.innerHTML = '';
    progressBar.style.width = '0%';

    const images = fileInput.files;

    for (let index = 0; index < images.length; index++) {
      const image = images[index];

      selectedImagesContainer.innerHTML += `
        <div class="d-flex justify-content-center align-items-center h-100">
          <img src="${URL.createObjectURL(image)}" class="w-75">
        </div>
      `;
    }

    processButton.disabled = false;
  });

  processButton.addEventListener('click', async () => {
    if (!fileInput.files) { return; }

    sendingFiles = true;

    processButton.disabled = true;
    cancelButton.disabled = false;

    const images = fileInput.files;

    for (let index = 0; index < images.length; index++) {
      if (!sendingFiles) { break; }

      const image = images[index];

      const reader = new FileReader();
      reader.readAsArrayBuffer(image);
      const imageArrayBuffer = await onReaderLoadPromise(reader)

      const response = await sendImage(imageArrayBuffer);
      if (response.status !== 200) {
        await alert('Error: Could not upload file to server.');
      }

      const responseBody = await decodeResponseBody(response);
      console.log(responseBody);

      const progress = Math.round(((index + 1) / images.length) * 100);
      progressBar.style.width = `${progress}%`;
      progressBar.innerHTML = `${progress}%`;
    }
  });

  cancelButton.addEventListener('click', () => {
    sendingFiles = false;

    processButton.disabled = true;
    cancelButton.disabled = true;
  });

  const onReaderLoadPromise = (reader: FileReader) => {
    return new Promise<string>((resolve, reject) => {
      reader.onload = () => {
        return resolve(reader.result as string);
      }
    });
  }
});